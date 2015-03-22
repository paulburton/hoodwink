#include "syscall.h"

uint32_t translate_sys_open(struct sys_state *sys, uint32_t *args)
{
	return sys_open(sys->mem_base + args[0], args[1], args[2]);
}

uint32_t translate_sys_openat(struct sys_state *sys, uint32_t *args)
{
	return sys_openat(args[0], sys->mem_base + args[1], args[2], args[3]);
}
