#include "syscall.h"

uint32_t translate_sys_fdatasync(const struct sys_state *sys, uint32_t *args)
{
	int fd = args[0];

	return sys_fdatasync(fd);
}

uint32_t translate_sys_fsync(const struct sys_state *sys, uint32_t *args)
{
	int fd = args[0];

	return sys_fsync(fd);
}
