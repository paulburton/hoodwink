#include "syscall.h"

uint32_t translate_sys_madvise(const struct sys_state *sys, uint32_t *args)
{
	void *addr = sys->mem_base + args[0];
	size_t length = args[1];
	int advice = args[2];

	return sys_madvise(addr, length, advice);
}
