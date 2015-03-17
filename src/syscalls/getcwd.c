#include "syscall.h"

uint32_t translate_sys_getcwd(struct sys_state *sys, uint32_t *args)
{
	return sys_getcwd(sys->mem_base + args[0], args[1]);
}
