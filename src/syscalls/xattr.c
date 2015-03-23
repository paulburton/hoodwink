#include "syscall.h"

uint32_t translate_sys_getxattr(const struct sys_state *sys, uint32_t *args)
{
	return sys_getxattr(sys->mem_base + args[0],
			    sys->mem_base + args[1],
			    args[2] ? sys->mem_base + args[2] : NULL,
			    args[3]);
}
