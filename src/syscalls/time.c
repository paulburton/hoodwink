#include "syscall.h"

uint32_t translate_sys_time(const struct sys_state *sys, uint32_t *args)
{
	time_t b = sys_time(NULL);
	front_time_t f = (front_time_t)b;

	if (args[0])
		*(front_time_t *)(sys->mem_base + args[0]) = f;

	return f;
}
