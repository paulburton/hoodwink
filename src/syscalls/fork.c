#include "syscall.h"

uint32_t translate_sys_fork(struct sys_state *sys, uint32_t *args)
{
	return sys_fork();
}
