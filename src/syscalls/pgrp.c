#include "syscall.h"

uint32_t translate_sys_getpgid(const struct sys_state *sys, uint32_t *args)
{
	return sys_getpgid(args[0]);
}

uint32_t translate_sys_setpgid(const struct sys_state *sys, uint32_t *args)
{
	return sys_setpgid(args[0], args[1]);
}

uint32_t translate_sys_getpgrp(const struct sys_state *sys, uint32_t *args)
{
	return sys_getpgrp();
}
