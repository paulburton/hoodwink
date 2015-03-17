#include "syscall.h"

uint32_t translate_sys_close(struct sys_state *sys, uint32_t *args)
{
	return sys_close(args[0]);
}
