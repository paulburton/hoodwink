#include "debug.h"
#include "syscall.h"

uint32_t translate_sys_waitpid(struct sys_state *sys, uint32_t *args)
{
	int *statusptr = args[1] ? sys->mem_base + args[1] : NULL;

	return sys_wait4((int32_t)args[0], statusptr, args[2], NULL);
}
