#include "syscall.h"

uint32_t translate_sys_mprotect(struct sys_state *sys, uint32_t *args)
{
	return sys_mprotect(sys->mem_base + args[0], args[1], args[2]);
}
