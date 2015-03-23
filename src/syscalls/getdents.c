#include "string.h"
#include "syscall.h"

uint32_t translate_sys_getdents(const struct sys_state *sys, uint32_t *args)
{
	front_linux_dirent_s *f = sys->mem_base + args[1];
	linux_dirent_s tmp, *b = sys->mem_base + args[1];
	int nread, sz, name_sz, pos;

	if (sizeof(*f) > sizeof(*b)) {
		/* in-place conversion won't work here! */
		return -FRONT_EINVAL;
	}

	nread = sys_getdents(args[0], b, args[2]);
	if (nread <= 0)
		return nread;

	sz = 0;

	for (pos = 0; pos < nread;) {
		b = sys->mem_base + args[1] + pos;
		f = sys->mem_base + args[1] + sz;

		tmp = *b;
		f->d_ino = tmp.d_ino;
		f->d_off = tmp.d_off;
		f->d_reclen = tmp.d_reclen;
		name_sz = tmp.d_reclen - __builtin_offsetof(linux_dirent_s, d_name);
		memcpy(f->d_name, tmp.d_name, name_sz);

		sz += __builtin_offsetof(front_linux_dirent_s, d_name) + name_sz;
	}

	return sz;
}

uint32_t translate_sys_getdents64(const struct sys_state *sys, uint32_t *args)
{
	return sys_getdents64(args[0], sys->mem_base + args[1], args[2]);
}
