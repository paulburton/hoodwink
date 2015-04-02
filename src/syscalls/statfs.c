#include "string.h"
#include "syscall.h"

static void b2f_statfs64(front_statfs64_s *f, const statfs_s *b)
{
	memset(f, 0, sizeof(*f));
	f->f_type = b->f_type;
	f->f_bsize = b->f_bsize;
	f->f_frsize = b->f_frsize;
	f->f_blocks = b->f_blocks;
	f->f_bfree = b->f_bfree;
	f->f_files = b->f_files;
	f->f_ffree = b->f_ffree;
	f->f_bavail = b->f_bavail;
	memcpy(f->f_fsid.val, b->f_fsid.val, sizeof(f->f_fsid.val));
	f->f_namelen = b->f_namelen;
	f->f_flags = b->f_flags;
}

uint32_t translate_sys_statfs64(const struct sys_state *sys, uint32_t *args)
{
	const char *pathname = sys->mem_base + args[0];
	size_t sz = args[1];
	front_statfs64_s *buf_f = sys->mem_base + args[2];
	statfs_s buf_b;
	int err;

	if (sz != sizeof(*buf_f))
		return -FRONT_EINVAL;

	err = sys_statfs(pathname, &buf_b);
	b2f_statfs64(buf_f, &buf_b);
	return err;
}
