#include "syscall.h"

uint32_t translate_sys_write(struct sys_state *sys, uint32_t *args)
{
	return sys_write(args[0], sys->mem_base + args[1], args[2]);
}
