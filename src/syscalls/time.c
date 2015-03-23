#include "syscall.h"

uint32_t translate_sys_time(const struct sys_state *sys, uint32_t *args)
{
	time_t b = sys_time(NULL);
	front_time_t f = (front_time_t)b;

	if (args[0])
		*(front_time_t *)(sys->mem_base + args[0]) = f;

	return f;
}

uint32_t translate_sys_times(const struct sys_state *sys, uint32_t *args)
{
	front_tms_s *f = sys->mem_base + args[0];
	tms_s b;
	clock_t ret;

	ret = sys_times(&b);

	f->tms_utime = b.tms_utime;
	f->tms_stime = b.tms_stime;
	f->tms_cutime = b.tms_cutime;
	f->tms_cstime = b.tms_cstime;

	return ret;
}
