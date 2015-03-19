#include "debug.h"
#include "mm.h"
#include "syscall.h"

uint32_t translate_sys_mmap(struct sys_state *sys, uint32_t *args)
{
	int prot, prot_ok;
	int flags, flags_ok;

	prot = f2b_prot(args[2], &prot_ok);
	if (!prot_ok) {
		debug("Unrecognised prot 0x%x\n", args[2]);
		return -FRONT_EINVAL;
	}

	flags = f2b_mmap_flags(args[3], &flags_ok);
	if (!flags_ok) {
		debug("Unrecognised mmap flags 0x%x\n", args[3]);
		return -FRONT_EINVAL;
	}

	return mm_mmap(sys, args[0], args[1], prot, flags, args[4], args[5]);
}

uint32_t translate_sys_mmap2(struct sys_state *sys, uint32_t *args)
{
	uint32_t nargs[6] = {
		args[0], args[1], args[2], args[3], args[4],
		args[5] * 4096,
	};

	return translate_sys_mmap(sys, nargs);
}
