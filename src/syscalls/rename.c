#include "syscall.h"

uint32_t translate_sys_rename(const struct sys_state *sys, uint32_t *args)
{
	const char *oldpath = args[0] ? sys->mem_base + args[0] : NULL;
	const char *newpath = args[1] ? sys->mem_base + args[1] : NULL;

	return sys_rename(oldpath, newpath);
}
