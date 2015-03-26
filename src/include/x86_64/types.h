#ifndef __hoodwink_x86_64_types_h__
#define __hoodwink_x86_64_types_h__

#include <stdint.h>

typedef int16_t		x86_64_short_t;
typedef uint16_t	x86_64_ushort_t;
typedef int32_t		x86_64_int_t;
typedef uint32_t	x86_64_uint_t;
typedef int64_t		x86_64_long_t;
typedef uint64_t	x86_64_ulong_t;

typedef int64_t		x86_64_clock_t;
typedef uint32_t	x86_64_gid_t;
typedef uint64_t	x86_64_loff_t;
typedef uint32_t	x86_64_mode_t;
typedef uint64_t	x86_64_off_t;
typedef int32_t		x86_64_pid_t;
typedef uint64_t	x86_64_sigset_t;
typedef uint64_t	x86_64_size_t;
typedef int64_t		x86_64_ssize_t;
typedef uint64_t	x86_64_time_t;
typedef uint32_t	x86_64_uid_t;

struct x86_64_iovec {
	uint64_t	iov_base;
	uint64_t	iov_len;
};

struct x86_64_linux_dirent {
	x86_64_ulong_t	d_ino;
	x86_64_ulong_t	d_off;
	x86_64_ushort_t	d_reclen;
	char		d_name[1];
};

struct x86_64_sigaction {
	uint64_t	sa_handler;
	uint64_t	sa_flags;
	uint64_t	sa_restorer;
	x86_64_sigset_t	sa_mask;
};

struct x86_64_sigaltstack {
	uint64_t	ss_sp;
	int32_t		ss_flags;
	x86_64_size_t	ss_size;
};

struct x86_64_sigcontext {
	uint64_t	r8;
	uint64_t	r9;
	uint64_t	r10;
	uint64_t	r11;
	uint64_t	r12;
	uint64_t	r13;
	uint64_t	r14;
	uint64_t	r15;
	uint64_t	rdi;
	uint64_t	rsi;
	uint64_t	rbp;
	uint64_t	rbx;
	uint64_t	rdx;
	uint64_t	rax;
	uint64_t	rcx;
	uint64_t	rsp;
	uint64_t	rip;
	uint64_t	eflags;
	uint16_t	cs;
	uint16_t	gs;
	uint16_t	fs;
	uint16_t	__pad0;
	uint64_t	err;
	uint64_t	trapno;
	uint64_t	oldmask;
	uint64_t	cr2;
	uint64_t	fpstate;
	uint64_t	reserved1[8];
};

struct x86_64_siginfo {
	int32_t		si_signo;
	int32_t		si_code;
	int32_t		si_errno;
	union {
		int32_t	_pad[29];

		struct {
			x86_64_pid_t	_pid;
			uint32_t	_uid;
			int32_t		_status;
			uint64_t	__attribute__((aligned(4))) _utime;
			uint64_t	__attribute__((aligned(4))) _stime;
		} _sigchld;
	} _sifields;
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

struct x86_64_termios {
	uint32_t	c_iflag;
	uint32_t	c_oflag;
	uint32_t	c_cflag;
	uint32_t	c_lflag;
	uint8_t		c_line;
	uint8_t		c_cc[19];
};

struct x86_64_timespec {
	x86_64_time_t	tv_sec;
	x86_64_long_t	tv_nsec;
};

struct x86_64_tms {
	x86_64_clock_t	tms_utime;
	x86_64_clock_t	tms_stime;
	x86_64_clock_t	tms_cutime;
	x86_64_clock_t	tms_cstime;
};

struct x86_64_ucontext {
	uint64_t	uc_flags;
	uint64_t	uc_link;
	struct x86_64_sigaltstack	uc_stack;
	struct x86_64_sigcontext	uc_mcontext;
	x86_64_sigset_t	uc_sigmask;
};

struct x86_64_utsname {
	char sysname[65];
	char nodename[65];
	char release[65];
	char version[65];
	char machine[65];
	char domainname[65];
};

struct x86_64_rt_sigframe {
	uint64_t	pretcode;
	struct x86_64_ucontext	uc;
	struct x86_64_siginfo	info;
};

#define X86_64_EINVAL		22

#define X86_64_F_GETFD		1
#define X86_64_F_GETFL		3

#define X86_64_MAP_SHARED	0x0001
#define X86_64_MAP_PRIVATE	0x0002
#define X86_64_MAP_FIXED	0x0010
#define X86_64_MAP_ANONYMOUS	0x0020
#define X86_64_MAP_DENYWRITE	0x0800

#define X86_64_O_RDONLY		0x00000
#define X86_64_O_WRONLY		0x00001
#define X86_64_O_RDWR		0x00002
#define X86_64_O_CREAT		0x00040
#define X86_64_O_EXCL		0x00080
#define X86_64_O_TRUNC		0x00200
#define X86_64_O_APPEND		0x00400
#define X86_64_O_NONBLOCK	0x00800
#define X86_64_O_LARGEFILE	0x08000
#define X86_64_O_DIRECTORY	0x10000
#define X86_64_O_CLOEXEC	0x80000

#define X86_64_PROT_NONE	0x0
#define X86_64_PROT_READ	0x1
#define X86_64_PROT_WRITE	0x2
#define X86_64_PROT_EXEC	0x4

#define X86_64_SA_SIGINFO	0x00000004
#define X86_64_SA_RESTORER	0x04000000

#define X86_64_SIGHUP		 1
#define X86_64_SIGINT		 2
#define X86_64_SIGQUIT		 3
#define X86_64_SIGILL		 4
#define X86_64_SIGTRAP		 5
#define X86_64_SIGABRT		 6
#define X86_64_SIGBUS		 7
#define X86_64_SIGFPE		 8
#define X86_64_SIGKILL		 9
#define X86_64_SIGUSR1		10
#define X86_64_SIGSEGV		11
#define X86_64_SIGUSR2		12
#define X86_64_SIGPIPE		13
#define X86_64_SIGALRM		14
#define X86_64_SIGTERM		15
#define X86_64_SIGSTKFLT	16
#define X86_64_SIGCHLD		17
#define X86_64_SIGCONT		18
#define X86_64_SIGSTOP		19
#define X86_64_SIGTSTP		20
#define X86_64_SIGTTIN		21
#define X86_64_SIGTTOU		22
#define X86_64_SIGURG		23
#define X86_64_SIGXCPU		24
#define X86_64_SIGXFSZ		25
#define X86_64_SIGVTALRM	26
#define X86_64_SIGPROF		27
#define X86_64_SIGWINCH		28
#define X86_64_SIGIO		29
#define X86_64_SIGPWR		30
#define X86_64_SIGSYS		31

#define X86_64_UTSNAME_MACHINE	"x86_64"

#endif /* __hoodwink_x86_64_types_h__ */
