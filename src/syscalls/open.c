#include "debug.h"
#include "syscall.h"

uint32_t translate_sys_open(const struct sys_state *sys, uint32_t *args)
{
	const char *pathname = sys->mem_base + args[0];
	int flags, flags_ok;
	mode_t mode = args[2];

	flags = f2b_open_flags(args[1], &flags_ok);
	if (!flags_ok) {
		debug("Unrecognised open flags 0x%x\n", args[1]);
		return -FRONT_EINVAL;
	}

	return sys_open(pathname, flags, mode);
}

uint32_t translate_sys_openat(const struct sys_state *sys, uint32_t *args)
{
	int dirfd = args[0];
	const char *pathname = sys->mem_base + args[1];
	int flags, flags_ok;
	mode_t mode = args[3];

	flags = f2b_open_flags(args[2], &flags_ok);
	if (!flags_ok) {
		debug("Unrecognised open flags 0x%x\n", args[2]);
		return -FRONT_EINVAL;
	}

	return sys_openat(dirfd, pathname, flags, mode);
}
