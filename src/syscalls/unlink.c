#include "syscall.h"

uint32_t translate_sys_unlink(const struct sys_state *sys, uint32_t *args)
{
	const char *pathname = sys->mem_base + args[0];

	return sys_unlink(pathname);
}

uint32_t translate_sys_unlinkat(const struct sys_state *sys, uint32_t *args)
{
	int dirfd = args[0];
	const char *pathname = sys->mem_base + args[1];
	int flags = args[1];

	return sys_unlinkat(dirfd, pathname, flags);
}
