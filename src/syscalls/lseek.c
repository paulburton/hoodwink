#include "syscall.h"

uint32_t translate_sys_lseek(const struct sys_state *sys, uint32_t *args)
{
	return sys_lseek(args[0], args[1], args[2]);
}

uint32_t translate_sys__llseek(const struct sys_state *sys, uint32_t *args)
{
	off_t off = ((uint64_t)args[1] << 32) | args[2];
	off_t result;

	result = sys_lseek(args[0], off, args[4]);

	if (args[3])
		*(front_loff_t *)(sys->mem_base + args[3]) = result;

	return IS_ERROR(result) ? result : 0;
}
