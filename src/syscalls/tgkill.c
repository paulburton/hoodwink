#include "syscall.h"

uint32_t translate_sys_tgkill(struct sys_state *sys, uint32_t *args)
{
	return sys_tgkill(args[0], args[1], args[2]);
}
