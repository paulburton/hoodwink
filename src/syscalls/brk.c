#include "debug.h"
#include "syscall.h"

uint32_t translate_sys_brk(struct sys_state *sys, uint32_t *args)
{
	int err;

	if (args[0] < sys->min_brk)
		return sys->brk;

	if (args[0] > sys->brk) {
		void *new_base = sys->mem_base + sys->brk;
		size_t new_sz = ((args[0] - sys->brk) + 4095) & ~4095;
		uint32_t new_brk = sys->brk + new_sz;

		debug("raise brk from 0x%x to 0x%x\n", sys->brk, new_brk);

		err = sys_mprotect(new_base, new_sz, PROT_READ | PROT_WRITE | PROT_EXEC);
		if (err)
			debug("Failed to mprotect memory region (%d)\n", err);
		else
			sys->brk = new_brk;
	} else {
		void *freed_base = sys->mem_base + args[0];
		size_t freed_sz = sys->brk - args[0];

		err = sys_mprotect(freed_base, freed_sz, PROT_NONE);
		if (err)
			debug("Failed to mprotect memory region\n");
		else
			sys->brk -= freed_sz;
	}

	return sys->brk;
}
