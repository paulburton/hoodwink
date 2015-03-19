#ifndef __hoodwink_mips32_types_h__
#define __hoodwink_mips32_types_h__

#include <stdint.h>

typedef int32_t		mips32_int_t;

typedef int32_t		mips32_gid_t;
typedef uint16_t	mips32_mode_t;
typedef uint32_t	mips32_off_t;
typedef int32_t		mips32_pid_t;
typedef uint32_t	mips32_sigset_t;
typedef uint32_t	mips32_size_t;
typedef int32_t		mips32_ssize_t;
typedef int32_t		mips32_time_t;
typedef int32_t		mips32_uid_t;

struct mips32_iovec {
	uint32_t	iov_base;
	uint32_t	iov_len;
};

struct mips32_sigaction {
	uint32_t	sa_handler;
	uint32_t	sa_flags;
	uint32_t	sa_restorer;
	mips32_sigset_t	sa_mask;
};

struct mips32_stat {
	/* TODO */
};

struct mips32_stat64 {
	uint32_t	st_dev;
	uint32_t	st_pad0[3];
	uint64_t	st_ino;
	mips32_mode_t	st_mode;
	uint32_t	st_nlink;
	mips32_uid_t	st_uid;
	mips32_gid_t	st_gid;
	uint32_t	st_rdev;
	uint32_t	st_pad1[3];
	uint64_t	st_size;
	mips32_time_t	st_atime;
	uint32_t	st_atime_nsec;
	mips32_time_t	st_mtime;
	uint32_t	st_mtime_nsec;
	mips32_time_t	st_ctime;
	uint32_t	st_ctime_nsec;
	uint32_t	st_blksize;
	uint32_t	st_pad2;
	uint64_t	st_blocks;
};

struct mips32_utsname {
	char sysname[65];
	char nodename[65];
	char release[65];
	char version[65];
	char machine[65];
};

#define MIPS32_EINVAL		22

#define MIPS32_MAP_SHARED	0x0001
#define MIPS32_MAP_PRIVATE	0x0002
#define MIPS32_MAP_FIXED	0x0010
#define MIPS32_MAP_ANONYMOUS	0x0800
#define MIPS32_MAP_DENYWRITE	0x2000

#define MIPS32_O_RDONLY		0x00000
#define MIPS32_O_WRONLY		0x00001
#define MIPS32_O_RDWR		0x00002
#define MIPS32_O_CREAT		0x00100
#define MIPS32_O_TRUNC		0x00200
#define MIPS32_O_CLOEXEC	0x80000

#define MIPS32_PROT_NONE	0x0
#define MIPS32_PROT_READ	0x1
#define MIPS32_PROT_WRITE	0x2
#define MIPS32_PROT_EXEC	0x4

#define MIPS32_SA_SIGINFO	0x00000004
#define MIPS32_SA_RESTORER	0x04000000

#define MIPS32_SIGSEGV		11

#endif /* __hoodwink_mips32_types_h__ */
