#include "debug.h"
#include "syscall.h"

uint32_t translate_sys_mprotect(struct sys_state *sys, uint32_t *args)
{
	int prot, prot_ok;

	prot = f2b_prot(args[2], &prot_ok);
	if (!prot_ok) {
		debug("Unrecognised prot 0x%x\n", args[2]);
		return -FRONT_EINVAL;
	}

	return sys_mprotect(sys->mem_base + args[0], args[1], prot);
}
