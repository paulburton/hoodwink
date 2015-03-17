#include "syscall.h"

uint32_t translate_sys_exit_group(struct sys_state *sys, uint32_t *args)
{
	sys_exit_group(args[0]);
	return -1;
}
