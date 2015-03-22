#include "syscall.h"

static void b2f_stat64(front_stat64_s *f, stat_s *b)
{
	f->st_dev = b->st_dev;
	f->st_ino = b->st_ino;
	f->st_mode = b->st_mode;
	f->st_nlink = b->st_nlink;
	f->st_uid = b->st_uid;
	f->st_gid = b->st_gid;
	f->st_rdev = b->st_rdev;
	f->st_size = b->st_size;
	f->st_atime = b->st_atime;
	f->st_atime_nsec = b->st_atime_nsec;
	f->st_mtime = b->st_mtime;
	f->st_mtime_nsec = b->st_mtime_nsec;
	f->st_ctime = b->st_ctime;
	f->st_ctime_nsec = b->st_ctime_nsec;
	f->st_blksize = b->st_blksize;
	f->st_blocks = b->st_blocks;
}

uint32_t translate_sys_fstat64(struct sys_state *sys, uint32_t *args)
{
	front_stat64_s *fbuf = sys->mem_base + args[1];
	stat_s bbuf;
	uint32_t err;

	err = sys_fstat(args[0], &bbuf);
	if (!err)
		b2f_stat64(fbuf, &bbuf);

	return err;
}

uint32_t translate_sys_lstat64(struct sys_state *sys, uint32_t *args)
{
	front_stat64_s *fbuf = sys->mem_base + args[1];
	stat_s bbuf;
	uint32_t err;

	err = sys_lstat(sys->mem_base + args[0], &bbuf);
	if (!err)
		b2f_stat64(fbuf, &bbuf);

	return err;
}

uint32_t translate_sys_stat64(struct sys_state *sys, uint32_t *args)
{
	front_stat64_s *fbuf = sys->mem_base + args[1];
	stat_s bbuf;
	uint32_t err;

	err = sys_stat(sys->mem_base + args[0], &bbuf);
	if (!err)
		b2f_stat64(fbuf, &bbuf);

	return err;
}
