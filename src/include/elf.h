#ifndef __hoodwink_elf_h__
#define __hoodwink_elf_h__

#include_next <elf.h>

#include "sys.h"

enum elf_load_flags {
	ELF_INTERP	= 1 << 0,
};

struct elf_load_info {
	uint32_t base;
	uint32_t entry;
	uint32_t interp_base;
	uint32_t phdr_base;
	unsigned phent;
	unsigned phnum;
};

extern uint32_t elf_load(struct sys_state *sys, void *base, int flags, struct elf_load_info *info);
extern uint32_t elf_load_fd(struct sys_state *sys, int fd, int flags, struct elf_load_info *info);
extern uint32_t elf_load_filename(struct sys_state *sys, const char *filename, int flags, struct elf_load_info *info);

#endif /* __hoodwink_elf_h__ */
