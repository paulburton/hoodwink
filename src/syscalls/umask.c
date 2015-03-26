#include "syscall.h"

uint32_t translate_sys_umask(const struct sys_state *sys, uint32_t *args)
{
	mode_t mask = args[0];

	return sys_umask(mask);
}
