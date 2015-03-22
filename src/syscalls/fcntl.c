#include "debug.h"
#include "syscall.h"

uint32_t translate_sys_fcntl64(const struct sys_state *sys, uint32_t *args)
{
	switch (args[1]) {
	case FRONT_F_GETFD:
		return sys_fcntl(args[0], F_GETFD, args[2]);

	case FRONT_F_GETFL:
		return sys_fcntl(args[0], F_GETFL, args[2]);

	default:
		debug_syscall("Unrecognised fcntl cmd 0x%x\n", args[1]);
		return -FRONT_EINVAL;
	}
}
