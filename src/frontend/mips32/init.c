#include "debug.h"
#include "elf.h"
#include "mips32.h"
#include "mm.h"
#include "string.h"
#include "sys.h"
#include "syscall.h"
#include "util.h"

static uint32_t push_string(struct mips32_state *mips, const char *str)
{
	size_t len = strlen(str) + 1;

	mips->cpu.gpr[29] -= len;
	mips->cpu.gpr[29] &= ~0x7;

	memcpy(mips->sys.mem_base + mips->cpu.gpr[29], str, len);
	*(char *)(mips->sys.mem_base + mips->cpu.gpr[29] + len) = 0;

	return mips->cpu.gpr[29];
}

static uint32_t push_u32(struct mips32_state *mips, uint32_t val)
{
	mips->cpu.gpr[29] -= 4;
	*(uint32_t *)(mips->sys.mem_base + mips->cpu.gpr[29]) = val;
	return mips->cpu.gpr[29];
}

static uint32_t push_aux(struct mips32_state *mips, uint32_t type, uint32_t val)
{
	push_u32(mips, val);
	return push_u32(mips, type);
}

void frontend_init(const char *filename)
{
	struct mips32_state mips;
	struct elf_load_info elf_info;
	unsigned stack_sz;
	int err, prot;
	uint32_t argv[2];
	uint32_t envp[1];

	memset(&mips, 0, sizeof(mips));

	mips.sys.mem_base = sys_mmap(NULL, (size_t)2 << 30, PROT_NONE,
				     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (IS_ERROR(mips.sys.mem_base)) {
		debug("Failed to mmap MIPS memory\n");
		sys_exit(1);
	}
	debug("MIPS memory at 0x%p\n", mips.sys.mem_base);

	mips.sys.page_bits = 12;
	mm_init(&mips.sys);

	stack_sz = 128 << 10;
	prot = PROT_READ | PROT_WRITE | PROT_EXEC;
	mips.cpu.gpr[29] = 0x7fff0000;
	err = sys_mprotect(mips.sys.mem_base + mips.cpu.gpr[29] - stack_sz,
			   stack_sz, prot);
	if (err) {
		debug("Failed to mprotect stack\n");
		sys_exit(1);
	}

	argv[0] = push_string(&mips, filename);
	argv[1] = push_string(&mips, "test_argv1");

	envp[0] = push_string(&mips, "LD_DEBUG=all");

	mips.cpu.pc = elf_load_filename(&mips.sys, filename, 0, &elf_info);
	mips.sys.min_brk = mips.sys.brk;

	push_aux(&mips, AT_NULL, 0);
	push_aux(&mips, AT_PAGESZ, 4 << 10);
	push_aux(&mips, AT_PHDR, elf_info.phdr_base);
	push_aux(&mips, AT_PHENT, elf_info.phent);
	push_aux(&mips, AT_PHNUM, elf_info.phnum);
	push_aux(&mips, AT_BASE, elf_info.interp_base);
	push_aux(&mips, AT_ENTRY, elf_info.entry);

	/* envp */
	push_u32(&mips, 0);
	push_u32(&mips, envp[0]);

	/* argv */
	push_u32(&mips, 0);
	push_u32(&mips, argv[0]);
	push_u32(&mips, argv[1]);

	/* argc */
	push_u32(&mips, 2);

	while (1)
		frontend_interp(&mips);
}
