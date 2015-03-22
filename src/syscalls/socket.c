#include "syscall.h"

uint32_t translate_sys_socket(const struct sys_state *sys, uint32_t *args)
{
	return sys_socket(args[0], args[1], args[2]);
}
