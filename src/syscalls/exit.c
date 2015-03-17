#include "syscall.h"

uint32_t translate_sys_exit(struct sys_state *sys, uint32_t *args)
{
	sys_exit(args[0]);
	return -1;
}
