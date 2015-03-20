#include "syscall.h"

uint32_t translate_sys_futex(struct sys_state *sys, uint32_t *args)
{
	front_timespec_s *f = sys->mem_base + args[3];
	timespec_s h;

	h.tv_sec = f->tv_sec;
	h.tv_nsec = f->tv_nsec;

	return sys_futex(sys->mem_base + args[0], args[1], args[2],
			 &h, sys->mem_base + args[4], args[5]);
}
