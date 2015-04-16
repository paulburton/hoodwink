#include "syscall.h"

uint32_t translate_sys_dup(const struct sys_state *sys, uint32_t *args)
{
	int oldfd = args[0];

	return sys_dup(oldfd);
}

uint32_t translate_sys_dup2(const struct sys_state *sys, uint32_t *args)
{
	int oldfd = args[0];
	int newfd = args[1];

	return sys_dup2(oldfd, newfd);
}

uint32_t translate_sys_dup3(const struct sys_state *sys, uint32_t *args)
{
	int oldfd = args[0];
	int newfd = args[1];
	int flags_f = args[2];
	int flags_b, flags_ok;

	flags_b = f2b_open_flags(flags_f, &flags_ok);
	if (!flags_ok)
		return -FRONT_EINVAL;

	return sys_dup3(oldfd, newfd, flags_b);
}
