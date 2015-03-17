#include "syscall.h"

uint32_t translate_sys_fstat64(struct sys_state *sys, uint32_t *args)
{
	front_stat64_s *fbuf = sys->mem_base + args[1];
	stat_s bbuf;
	uint32_t err;

	err = sys_fstat(args[0], &bbuf);
	if (!err) {
		fbuf->st_dev = bbuf.st_dev;
		fbuf->st_ino = bbuf.st_ino;
		fbuf->st_mode = bbuf.st_mode;
		fbuf->st_nlink = bbuf.st_nlink;
		fbuf->st_uid = bbuf.st_uid;
		fbuf->st_gid = bbuf.st_gid;
		fbuf->st_rdev = bbuf.st_rdev;
		fbuf->st_size = bbuf.st_size;
		fbuf->st_atime = bbuf.st_atime;
		fbuf->st_atime_nsec = bbuf.st_atime_nsec;
		fbuf->st_mtime = bbuf.st_mtime;
		fbuf->st_mtime_nsec = bbuf.st_mtime_nsec;
		fbuf->st_ctime = bbuf.st_ctime;
		fbuf->st_ctime_nsec = bbuf.st_ctime_nsec;
		fbuf->st_blksize = bbuf.st_blksize;
		fbuf->st_blocks = bbuf.st_blocks;
	}

	return err;
}
