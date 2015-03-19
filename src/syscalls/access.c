#include "syscall.h"

uint32_t translate_sys_access(struct sys_state *sys, uint32_t *args)
{
	return sys_access(sys->mem_base + args[0], args[1]);
}
