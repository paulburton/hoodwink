#include "syscall.h"

uint32_t translate_sys_getgid(const struct sys_state *sys, uint32_t *args)
{
	return sys_getgid();
}

uint32_t translate_sys_setgid(const struct sys_state *sys, uint32_t *args)
{
	gid_t gid = args[0];

	return sys_setgid(gid);
}
