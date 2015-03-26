#include "debug.h"
#include "syscall.h"

uint32_t translate_sys_mkdir(const struct sys_state *sys, uint32_t *args)
{
	const char *pathname = sys->mem_base + args[0];
	mode_t mode = args[1];

	debug("mkdir \"%s\"\n", pathname);
	return sys_mkdir(pathname, mode);
}

uint32_t translate_sys_mkdirat(const struct sys_state *sys, uint32_t *args)
{
	int dirfd = args[0];
	const char *pathname = sys->mem_base + args[1];
	mode_t mode = args[2];

	return sys_mkdirat(dirfd, pathname, mode);
}
