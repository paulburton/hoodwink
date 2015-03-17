#include "syscall.h"

uint32_t translate_sys_geteuid(struct sys_state *sys, uint32_t *args)
{
	return sys_geteuid();
}
