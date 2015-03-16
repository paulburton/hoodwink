#include "debug.h"
#include "elf.h"
#include "string.h"
#include "syscall.h"
#include "util.h"

uint32_t elf_load(struct sys_state *sys, void *base, int flags, struct elf_load_info *info)
{
	unsigned aligned_sz, align_pad;
	void *aligned_base;
	char *interp_filename = NULL;
	Elf32_Ehdr *ehdr = base;
	Elf32_Phdr *phdr;
	int i, prot, err;
	int have_loadaddr = 0;
	uint32_t entry;

	if (ehdr->e_version != 1) {
		debug("ELF version invalid\n");
		sys_exit(1);
	}

	if (ehdr->e_machine != EM_MIPS) {
		debug("ELF machine invalid\n");
		sys_exit(1);
	}

	debug("ELF header looks valid\n");

	if (info && !(flags & ELF_INTERP)) {
		info->phent = ehdr->e_phentsize;
		info->phnum = ehdr->e_phnum;
	}

	entry = ehdr->e_entry;

	for (i = 0; i < ehdr->e_phnum; i++) {
		phdr = base + ehdr->e_phoff + (i * ehdr->e_phentsize);

		debug("Phdr[%d] type 0x%x off 0x%x vaddr 0x%x paddr 0x%x filesz 0x%x "
		      "memsz 0x%x flags 0x%x align 0x%x\n", i,
		      phdr->p_type, phdr->p_offset, phdr->p_vaddr, phdr->p_paddr,
		      phdr->p_filesz, phdr->p_memsz, phdr->p_flags, phdr->p_align);

		if (phdr->p_type == PT_LOAD) {
			prot = 0;

			if (phdr->p_flags & PF_X)
				prot |= PROT_EXEC;
			if (phdr->p_flags & PF_W)
				prot |= PROT_WRITE;
			if (phdr->p_flags & PF_R)
				prot |= PROT_READ;

			align_pad = phdr->p_vaddr & (phdr->p_align - 1);
			aligned_base = sys->mem_base + phdr->p_vaddr - align_pad;
			aligned_sz = phdr->p_memsz + align_pad;

			aligned_sz += 4095;
			aligned_sz &= ~4095;

			err = sys_mprotect(aligned_base, aligned_sz, prot | PROT_WRITE);
			if (err) {
				debug("Failed to mprotect memory region\n");
				sys_exit(1);
			}

			memcpy(sys->mem_base + phdr->p_vaddr, base + phdr->p_offset, phdr->p_filesz);

			if (phdr->p_memsz > phdr->p_filesz)
				memset(sys->mem_base + phdr->p_vaddr + phdr->p_filesz,
				       0, phdr->p_memsz - phdr->p_filesz);

			if (!(prot & PROT_WRITE)) {
				err = sys_mprotect(aligned_base, aligned_sz, prot);
				if (err) {
					debug("Failed to mprotect memory region\n");
					sys_exit(1);
				}
			}

			sys->brk = max(sys->brk, aligned_base + aligned_sz - sys->mem_base);

			if (info && !(flags & ELF_INTERP) && !have_loadaddr) {
				uint32_t load_addr = phdr->p_vaddr - phdr->p_offset;
				have_loadaddr = 1;
				info->phdr_base = load_addr + ehdr->e_phoff;
			}
		}

		if (phdr->p_type == PT_INTERP)
			interp_filename = base + phdr->p_offset;
	}

	if (!(flags & ELF_INTERP) && interp_filename) {
		debug("Load interpreter \"%s\"\n", interp_filename);
		entry = elf_load_filename(sys, interp_filename, ELF_INTERP, info);
		if (info)
			info->interp_base = entry;
	}

	if (info && !(flags & ELF_INTERP))
		info->entry = entry;

	return entry;
}

uint32_t elf_load_fd(struct sys_state *sys, int fd, int flags, struct elf_load_info *info)
{
	uint32_t entry;
	stat_s stat;
	void *base;
	int err;

	err = sys_fstat(fd, &stat);
	if (err) {
		debug("Failed to stat ELF (%d)\n", err);
		sys_exit(1);
	}

	base = sys_mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (IS_ERROR(base)) {
		debug("Failed to mmap ELF file\n");
		sys_exit(1);
	}

	entry = elf_load(sys, base, flags, info);
	sys_munmap(base, stat.st_size);
	return entry;
}

uint32_t elf_load_filename(struct sys_state *sys, const char *filename, int flags, struct elf_load_info *info)
{
	uint32_t entry;
	int fd;

	fd = sys_open(filename, O_RDONLY, 0);
	if (fd < 0) {
		debug("Failed to open ELF \"%s\"\n", filename);
		sys_exit(fd);
	}

	entry = elf_load_fd(sys, fd, flags, info);
	sys_close(fd);
	return entry;
}
