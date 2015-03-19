#include "syscall.h"

uint32_t translate_sys_lseek(struct sys_state *sys, uint32_t *args)
{
	return sys_lseek(args[0], args[1], args[2]);
}
