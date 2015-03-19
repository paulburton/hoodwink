#ifndef __hoodwink_x86_64_types_h__
#define __hoodwink_x86_64_types_h__

#include <stdint.h>

typedef int32_t		x86_64_int_t;

typedef uint32_t	x86_64_gid_t;
typedef uint32_t	x86_64_mode_t;
typedef uint64_t	x86_64_off_t;
typedef int32_t		x86_64_pid_t;
typedef uint64_t	x86_64_sigset_t;
typedef uint64_t	x86_64_size_t;
typedef int64_t		x86_64_ssize_t;
typedef uint32_t	x86_64_uid_t;

struct x86_64_iovec {
	uint64_t	iov_base;
	uint64_t	iov_len;
};

struct x86_64_sigaction {
	uint64_t	sa_handler;
	uint64_t	sa_flags;
	uint64_t	sa_restorer;
	x86_64_sigset_t	sa_mask;
};

struct x86_64_stat {
	uint64_t	st_dev;
	uint64_t	st_ino;
	uint64_t	st_nlink;
	uint32_t	st_mode;
	uint32_t	st_uid;
	uint32_t	st_gid;
	uint32_t	__pad0;
	uint64_t	st_rdev;
	int64_t		st_size;
	int64_t		st_blksize;
	int64_t		st_blocks;
	uint64_t	st_atime;
	uint64_t	st_atime_nsec;
	uint64_t	st_mtime;
	uint64_t	st_mtime_nsec;
	uint64_t	st_ctime;
	uint64_t	st_ctime_nsec;
	int64_t		__unused[3];
};

struct x86_64_stat64 {
	/* dummy */
};

struct x86_64_utsname {
	char sysname[65];
	char nodename[65];
	char release[65];
	char version[65];
	char machine[65];
	char domainname[65];
};

#define X86_64_EINVAL		22

#define X86_64_MAP_SHARED	0x0001
#define X86_64_MAP_PRIVATE	0x0002
#define X86_64_MAP_FIXED	0x0010
#define X86_64_MAP_ANONYMOUS	0x0020
#define X86_64_MAP_DENYWRITE	0x0800

#define X86_64_O_RDONLY		0x00000
#define X86_64_O_WRONLY		0x00001
#define X86_64_O_RDWR		0x00002
#define X86_64_O_CREAT	00000100
#define X86_64_O_TRUNC	00001000
#define X86_64_O_CLOEXEC	0x80000

#define X86_64_PROT_NONE	0x0
#define X86_64_PROT_READ	0x1
#define X86_64_PROT_WRITE	0x2
#define X86_64_PROT_EXEC	0x4

#define X86_64_SA_SIGINFO	0x00000004
#define X86_64_SA_RESTORER	0x04000000

#define X86_64_SIGSEGV		11

#endif /* __hoodwink_x86_64_types_h__ */
