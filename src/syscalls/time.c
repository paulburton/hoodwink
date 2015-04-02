#include "syscall.h"

uint32_t translate_sys_clock_gettime(const struct sys_state *sys, uint32_t *args)
{
	int err, clk_id = args[0];
	front_timespec_s *ts_f = args[1] ? sys->mem_base + args[1] : NULL;
	timespec_s ts_b, *pts_b = ts_f ? &ts_b : NULL;

	err = sys_clock_gettime(clk_id, pts_b);

	if (ts_f) {
		ts_f->tv_sec = ts_b.tv_sec;
		ts_f->tv_nsec = ts_b.tv_nsec;
	}

	return err;
}

uint32_t translate_sys_gettimeofday(const struct sys_state *sys, uint32_t *args)
{
	front_timeval_s *tv_f = args[0] ? sys->mem_base + args[0] : NULL;
	front_timezone_s *tz_f = args[1] ? sys->mem_base + args[1] : NULL;
	timeval_s tv_b, *ptv_b = tv_f ? &tv_b : NULL;
	timezone_s tz_b, *ptz_b = tz_f ? &tz_b : NULL;
	int err;

	err = sys_gettimeofday(ptv_b, ptz_b);

	if (tv_f) {
		tv_f->tv_sec = tv_b.tv_sec;
		tv_f->tv_usec = tv_b.tv_usec;
	}

	if (tz_f) {
		tz_f->tz_minuteswest = tz_b.tz_minuteswest;
		tz_f->tz_dsttime = tz_b.tz_dsttime;
	}

	return err;
}

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
