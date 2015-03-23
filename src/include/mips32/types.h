#ifndef __hoodwink_mips32_types_h__
#define __hoodwink_mips32_types_h__

#include <stdint.h>

typedef int16_t		mips32_short_t;
typedef uint16_t	mips32_ushort_t;
typedef int32_t		mips32_int_t;
typedef uint32_t	mips32_uint_t;
typedef int32_t		mips32_long_t;
typedef uint32_t	mips32_ulong_t;

typedef int32_t		mips32_clock_t;
typedef int32_t		mips32_gid_t;
typedef uint32_t	mips32_loff_t;
typedef uint16_t	mips32_mode_t;
typedef uint32_t	mips32_off_t;
typedef int32_t		mips32_pid_t;
typedef uint64_t	mips32_sigset_t[2];
typedef uint32_t	mips32_size_t;
typedef int32_t		mips32_ssize_t;
typedef int32_t		mips32_time_t;
typedef int32_t		mips32_uid_t;

struct mips32_iovec {
	uint32_t	iov_base;
	uint32_t	iov_len;
};

struct mips32_linux_dirent {
	mips32_ulong_t	d_ino;
	mips32_ulong_t	d_off;
	mips32_ushort_t	d_reclen;
	char		d_name[1];
};

struct mips32_sigaction {
	uint32_t	sa_flags;
	uint32_t	sa_handler;
	mips32_sigset_t	sa_mask;
};

struct mips32_sigaltstack {
	uint32_t	ss_sp;
	mips32_size_t	ss_size;
	int32_t		ss_flags;
};

struct mips32_sigcontext {
	uint32_t	sc_regmask;
	uint32_t	sc_status;
	uint64_t	sc_pc;
	uint64_t	sc_regs[32];
	uint64_t	sc_fpregs[32];
	uint32_t	sc_acx;
	uint32_t	sc_fpc_csr;
	uint32_t	sc_fpc_eir;
	uint32_t	sc_used_math;
	uint32_t	sc_dsp;
	uint64_t	sc_mdhi;
	uint64_t	sc_mdlo;
	uint32_t	sc_hi1;
	uint32_t	sc_lo1;
	uint32_t	sc_hi2;
	uint32_t	sc_lo2;
	uint32_t	sc_hi3;
	uint32_t	sc_lo3;
};

struct mips32_sigframe {
	uint32_t	sf_ass[4];
	uint32_t	sf_pad[2];
	struct mips32_sigcontext	sf_sc;
	mips32_sigset_t	sf_mask;
};

struct mips32_siginfo {
	int32_t		si_signo;
	int32_t		si_code;
	int32_t		si_errno;
	union {
		int32_t	_pad[29];

		struct {
			mips32_pid_t	_pid;
			uint32_t	_uid;
			int32_t		_status;
			mips32_clock_t	_utime;
			mips32_clock_t	_stime;
		} _sigchld;
	} _sifields;
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

struct mips32_termios {
	uint32_t	c_iflag;
	uint32_t	c_oflag;
	uint32_t	c_cflag;
	uint32_t	c_lflag;
	uint8_t		c_line;
	uint8_t		c_cc[23];
};

struct mips32_timespec {
	mips32_time_t	tv_sec;
	mips32_long_t	tv_nsec;
};

struct mips32_ucontext {
	uint32_t	uc_flags;
	uint32_t	uc_link;
	struct mips32_sigaltstack	uc_stack;
	struct mips32_sigcontext	uc_mcontext;
	mips32_sigset_t	uc_sigmask;
};

struct mips32_utsname {
	char sysname[65];
	char nodename[65];
	char release[65];
	char version[65];
	char machine[65];
};

struct mips32_rt_sigframe {
	uint32_t	sf_ass[4];
	uint32_t	sf_pad[2];
	struct mips32_siginfo	rs_info;
	struct mips32_ucontext	rs_uc;
};

#define MIPS32_EINVAL		22

#define MIPS32_F_GETFD		1
#define MIPS32_F_GETFL		3

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

#define MIPS32_SIGHUP		1
#define MIPS32_SIGINT		2
#define MIPS32_SIGQUIT		3
#define MIPS32_SIGILL		4
#define MIPS32_SIGTRAP		5
#define MIPS32_SIGABRT		6
#define MIPS32_SIGEMT		7
#define MIPS32_SIGFPE		8
#define MIPS32_SIGKILL		9
#define MIPS32_SIGBUS		10
#define MIPS32_SIGSEGV		11
#define MIPS32_SIGSYS		12
#define MIPS32_SIGPIPE		13
#define MIPS32_SIGALRM		14
#define MIPS32_SIGTERM		15
#define MIPS32_SIGUSR1		16
#define MIPS32_SIGUSR2		17
#define MIPS32_SIGCHLD		18
#define MIPS32_SIGPWR		19
#define MIPS32_SIGWINCH		20
#define MIPS32_SIGURG		21
#define MIPS32_SIGIO		22
#define MIPS32_SIGSTOP		23
#define MIPS32_SIGTSTP		24
#define MIPS32_SIGCONT		25
#define MIPS32_SIGTTIN		26
#define MIPS32_SIGTTOU		27
#define MIPS32_SIGVTALRM	28
#define MIPS32_SIGPROF		29
#define MIPS32_SIGXCPU		30
#define MIPS32_SIGXFSZ		31

#define MIPS32_UTSNAME_MACHINE	"mips"

#endif /* __hoodwink_mips32_types_h__ */
