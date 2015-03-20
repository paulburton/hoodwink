#include "syscall.h"

uint32_t translate_sys_getppid(struct sys_state *sys, uint32_t *args)
{
	return sys_getppid();
}
