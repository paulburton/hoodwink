#include "syscall.h"

uint32_t translate_sys_waitpid(struct sys_state *sys, uint32_t *args)
{
	int status, *statusptr;
	pid_t ret;

	statusptr = args[1] ? &status : NULL;

	ret = sys_wait4((int32_t)args[0], statusptr, args[2], NULL);
	if (!IS_ERROR(ret)) {
		if (statusptr)
			*(front_int_t *)(sys->mem_base + args[1]) = status;
	}

	return ret;
}
