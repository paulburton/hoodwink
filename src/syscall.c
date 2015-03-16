#include "debug.h"
#include "string.h"
#include "syscall.h"
#include "util.h"

#define NUM_OFFSET SYSCALL_NR_FRONT(_min)

#define SYSCALL(_name, _ret, ...) [SYSCALL_NR_FRONT(_name) - NUM_OFFSET] = {	\
	.name = #_name,								\
	.nargs = VA_NUM_ARGS(__VA_ARGS__),					\
},

static const struct syscall_info {
	char *name;
	unsigned nargs;
} syscall_info[] = {
#include "syscall-list.h"
};

#undef SYSCALL

extern int translate_sys_uname(front_utsname_s *buf);

void frontend_syscall_invoke(struct sys_state *sys, unsigned num)
{
	const struct syscall_info *info;
	uint32_t args[8], ret;
	unsigned nargs;
	int i, err;

	if ((num - NUM_OFFSET) < ARRAY_SIZE(syscall_info)) {
		info = &syscall_info[num - NUM_OFFSET];
		if (!info->name)
			info = NULL;
	} else {
		info = NULL;
	}

	nargs = info ? info->nargs : 0;
	frontend_syscall_args(sys, nargs, args);

	debug("syscall %u %s(", num, info ? info->name : "UNKNOWN");
	for (i = 0; i < nargs; i++)
		debug("%s0x%x", i ? ", " : "", args[i]);
	debug(")\n");

	switch (num) {
	case SYSCALL_NR_FRONT(brk):
		if (args[0] < sys->min_brk) {
			ret = sys->brk;
			break;
		}

		if (args[0] > sys->brk) {
			void *new_base = sys->mem_base + sys->brk;
			size_t new_sz = ((args[0] - sys->brk) + 4095) & ~4095;
			uint32_t new_brk = sys->brk + new_sz;

			debug("raise brk from 0x%x to 0x%x\n", sys->brk, new_brk);

			err = sys_mprotect(new_base, new_sz, PROT_READ | PROT_WRITE | PROT_EXEC);
			if (err)
				debug("Failed to mprotect memory region (%d)\n", err);
			else
				sys->brk = new_brk;
		} else {
			void *freed_base = sys->mem_base + args[0];
			size_t freed_sz = sys->brk - args[0];

			err = sys_mprotect(freed_base, freed_sz, PROT_NONE);
			if (err)
				debug("Failed to mprotect memory region\n");
			else
				sys->brk -= freed_sz;
		}

		ret = sys->brk;
		break;

	case SYSCALL_NR_FRONT(close):
		ret = sys_close(args[0]);
		break;

	case SYSCALL_NR_FRONT(exit):
		sys_exit(args[0]);
		ret = -1;
		break;

	case SYSCALL_NR_FRONT(exit_group):
		sys_exit_group(args[0]);
		ret = -1;
		break;

	case SYSCALL_NR_FRONT(fstat64):
		{
			front_stat64_s *fbuf = sys->mem_base + args[1];
			stat_s bbuf;
			ret = sys_fstat(args[0], &bbuf);
			if (!ret) {
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
		}
		break;

	case SYSCALL_NR_FRONT(getpid):
		ret = sys_getpid();
		break;

	case SYSCALL_NR_FRONT(mmap):
		ret = -1;
		break;

	case SYSCALL_NR_FRONT(open):
		ret = sys_open(sys->mem_base + args[0], args[1], args[2]);
		break;

	case SYSCALL_NR_FRONT(read):
		ret = sys_read(args[0], sys->mem_base + args[1], args[2]);
		break;

	case SYSCALL_NR_FRONT(uname):
		ret = translate_sys_uname(sys->mem_base + args[0]);
		break;

	case SYSCALL_NR_FRONT(write):
		ret = sys_write(args[0], sys->mem_base + args[1], args[2]);
		break;

	case SYSCALL_NR_FRONT(writev):
		{
			front_iovec_s *fvec = sys->mem_base + args[1];
			iovec_s bvec[args[2]];

			for (i = 0; i < args[2]; i++) {
				bvec[i].iov_base = (uintptr_t)(sys->mem_base + fvec[i].iov_base);
				bvec[i].iov_len = fvec[i].iov_len;
			}

			ret = sys_writev(args[0], bvec, args[2]);
		}
		break;

	default:
		ret = frontend_syscall_arch_invoke(sys, num, args);
		break;
	}

	frontend_syscall_ret(sys, ret);
}
