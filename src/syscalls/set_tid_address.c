#include "syscall.h"

uint32_t translate_sys_set_tid_address(const struct sys_state *sys, uint32_t *args)
{
	int *tidptr = args[0] ? sys->mem_base + args[0] : NULL;

	return sys_set_tid_address(tidptr);
}
