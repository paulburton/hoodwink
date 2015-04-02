#ifndef __hoodwink_types_h__
#define __hoodwink_types_h__

#include <stdint.h>

#include "config.h"
#include "util.h"

#if defined(FRONT_ARCH_MIPS32) || defined(BACK_ARCH_MIPS32)
# include "mips32/types.h"
#endif
#if defined(FRONT_ARCH_X86_64) || defined(BACK_ARCH_X86_64)
# include "x86_64/types.h"
#endif

#define NULL		((void *)0)

#define CLONE_VM	0x00000100
#define CLONE_SETTLS	0x00080000

/* mode_t */
#define S_IRWXU		00700
#define S_IRUSR		00400
#define S_IWUSR		00200
#define S_IXUSR		00100
#define S_IRWXG		00070
#define S_IRGRP		00040
#define S_IWGRP		00020
#define S_IXGRP		00010
#define S_IRWXO		00007
#define S_IROTH		00004
#define S_IWOTH		00002
#define S_IXOTH		00001

#define BACK_UTSNAME_MACHINE \
	CAT(BACK_ARCH, _UTSNAME_MACHINE)
#define FRONT_UTSNAME_MACHINE \
	CAT(FRONT_ARCH, _UTSNAME_MACHINE)

#define F_GETFD		CAT(BACK_ARCH, _F_GETFD)
#define F_GETFL		CAT(BACK_ARCH, _F_GETFL)

#define FRONT_F_GETFD	CAT(FRONT_ARCH, _F_GETFD)
#define FRONT_F_GETFL	CAT(FRONT_ARCH, _F_GETFL)

#define SIGABRT		CAT(BACK_ARCH, _SIGABRT)
#define SIGBUS		CAT(BACK_ARCH, _SIGBUS)
#define SIGCHLD		CAT(BACK_ARCH, _SIGCHLD)
#define SIGCONT		CAT(BACK_ARCH, _SIGCONT)
#define SIGFPE		CAT(BACK_ARCH, _SIGFPE)
#define SIGHUP		CAT(BACK_ARCH, _SIGHUP)
#define SIGILL		CAT(BACK_ARCH, _SIGILL)
#define SIGINT		CAT(BACK_ARCH, _SIGINT)
#define SIGKILL		CAT(BACK_ARCH, _SIGKILL)
#define SIGPIPE		CAT(BACK_ARCH, _SIGPIPE)
#define SIGPROF		CAT(BACK_ARCH, _SIGPROF)
#define SIGQUIT		CAT(BACK_ARCH, _SIGQUIT)
#define SIGSEGV		CAT(BACK_ARCH, _SIGSEGV)
#define SIGTRAP		CAT(BACK_ARCH, _SIGTRAP)
#define SIGTSTP		CAT(BACK_ARCH, _SIGTSTP)
#define SIGTTIN		CAT(BACK_ARCH, _SIGTTIN)
#define SIGTTOU		CAT(BACK_ARCH, _SIGTTOU)
#define SIGUSR1		CAT(BACK_ARCH, _SIGUSR1)
#define SIGUSR2		CAT(BACK_ARCH, _SIGUSR2)
#define SIGVTALRM	CAT(BACK_ARCH, _SIGVTALRM)
#define SIGXCPU		CAT(BACK_ARCH, _SIGXCPU)

#define FRONT_SIGABRT	CAT(FRONT_ARCH, _SIGABRT)
#define FRONT_SIGBUS	CAT(FRONT_ARCH, _SIGBUS)
#define FRONT_SIGCHLD	CAT(FRONT_ARCH, _SIGCHLD)
#define FRONT_SIGCONT	CAT(FRONT_ARCH, _SIGCONT)
#define FRONT_SIGFPE	CAT(FRONT_ARCH, _SIGFPE)
#define FRONT_SIGHUP	CAT(FRONT_ARCH, _SIGHUP)
#define FRONT_SIGILL	CAT(FRONT_ARCH, _SIGILL)
#define FRONT_SIGINT	CAT(FRONT_ARCH, _SIGINT)
#define FRONT_SIGKILL	CAT(FRONT_ARCH, _SIGKILL)
#define FRONT_SIGPIPE	CAT(FRONT_ARCH, _SIGPIPE)
#define FRONT_SIGPROF	CAT(FRONT_ARCH, _SIGPROF)
#define FRONT_SIGQUIT	CAT(FRONT_ARCH, _SIGQUIT)
#define FRONT_SIGSEGV	CAT(FRONT_ARCH, _SIGSEGV)
#define FRONT_SIGTRAP	CAT(FRONT_ARCH, _SIGTRAP)
#define FRONT_SIGTSTP	CAT(FRONT_ARCH, _SIGTSTP)
#define FRONT_SIGTTIN	CAT(FRONT_ARCH, _SIGTTIN)
#define FRONT_SIGTTOU	CAT(FRONT_ARCH, _SIGTTOU)
#define FRONT_SIGUSR1	CAT(FRONT_ARCH, _SIGUSR1)
#define FRONT_SIGUSR2	CAT(FRONT_ARCH, _SIGUSR2)
#define FRONT_SIGVTALRM	CAT(FRONT_ARCH, _SIGVTALRM)
#define FRONT_SIGXCPU	CAT(FRONT_ARCH, _SIGXCPU)

#define DECLARE_TYPEDEFS(arch, prefix)					\
	typedef arch##_clock_t			prefix##clock_t;	\
	typedef arch##_int_t			prefix##int_t;		\
	typedef arch##_gid_t			prefix##gid_t;		\
	typedef arch##_loff_t			prefix##loff_t;		\
	typedef arch##_long_t			prefix##long_t;		\
	typedef arch##_mode_t			prefix##mode_t;		\
	typedef arch##_off_t			prefix##off_t;		\
	typedef arch##_pid_t			prefix##pid_t;		\
	typedef arch##_sigset_t			prefix##sigset_t;	\
	typedef arch##_size_t			prefix##size_t;		\
	typedef arch##_ssize_t			prefix##ssize_t;	\
	typedef arch##_time_t			prefix##time_t;		\
	typedef arch##_uid_t			prefix##uid_t;		\
	typedef arch##_ulong_t			prefix##ulong_t;	\
	typedef struct arch##_iovec		prefix##iovec_s;	\
	typedef struct arch##_linux_dirent	prefix##linux_dirent_s;	\
	typedef struct arch##_rt_sigframe	prefix##rt_sigframe_s;	\
	typedef struct arch##_sigaction		prefix##sigaction_s;	\
	typedef struct arch##_sigaltstack	prefix##sigaltstack_s;	\
	typedef struct arch##_sigcontext	prefix##sigcontext_s;	\
	typedef struct arch##_siginfo		prefix##siginfo_s;	\
	typedef struct arch##_stat		prefix##stat_s;		\
	typedef struct arch##_stat64		prefix##stat64_s;	\
	typedef struct arch##_termios		prefix##termios_s;	\
	typedef struct arch##_timespec		prefix##timespec_s;	\
	typedef struct arch##_tms		prefix##tms_s;		\
	typedef struct arch##_ucontext		prefix##ucontext_s;	\
	typedef struct arch##_utsname		prefix##utsname_s;

#define DECLARE_CONSTANTS(arch, prefix)					\
	static const int prefix##EINVAL = arch##_EINVAL;		\
	static const int prefix##MAP_ANONYMOUS = arch##_MAP_ANONYMOUS;	\
	static const int prefix##MAP_DENYWRITE = arch##_MAP_DENYWRITE;	\
	static const int prefix##MAP_FIXED = arch##_MAP_FIXED;		\
	static const int prefix##MAP_PRIVATE = arch##_MAP_PRIVATE;	\
	static const int prefix##MAP_SHARED = arch##_MAP_SHARED;	\
	static const int prefix##O_RDONLY = arch##_O_RDONLY;		\
	static const int prefix##O_WRONLY = arch##_O_WRONLY;		\
	static const int prefix##O_RDWR = arch##_O_RDWR;		\
	static const int prefix##O_CREAT = arch##_O_CREAT;		\
	static const int prefix##O_EXCL = arch##_O_EXCL;		\
	static const int prefix##O_TRUNC = arch##_O_TRUNC;		\
	static const int prefix##O_APPEND = arch##_O_APPEND;		\
	static const int prefix##O_NONBLOCK = arch##_O_NONBLOCK;	\
	static const int prefix##O_LARGEFILE = arch##_O_LARGEFILE;	\
	static const int prefix##O_DIRECTORY = arch##_O_DIRECTORY;	\
	static const int prefix##O_CLOEXEC = arch##_O_CLOEXEC;		\
	static const int prefix##POLL_IN = arch##_POLL_IN;		\
	static const int prefix##POLL_OUT = arch##_POLL_OUT;		\
	static const int prefix##POLL_PRI = arch##_POLL_PRI;		\
	static const int prefix##POLL_RDBAND = arch##_POLL_RDBAND;	\
	static const int prefix##POLL_RDNORM = arch##_POLL_RDNORM;	\
	static const int prefix##POLL_WRBAND = arch##_POLL_WRBAND;	\
	static const int prefix##POLL_WRNORM = arch##_POLL_WRNORM;	\
	static const int prefix##PROT_NONE = arch##_PROT_NONE;		\
	static const int prefix##PROT_EXEC = arch##_PROT_EXEC;		\
	static const int prefix##PROT_READ = arch##_PROT_READ;		\
	static const int prefix##PROT_WRITE = arch##_PROT_WRITE;	\
	static const int prefix##SA_RESTORER = arch##_SA_RESTORER;	\
	static const int prefix##SA_SIGINFO = arch##_SA_SIGINFO;

#ifdef BACK_ARCH_X86_64
DECLARE_TYPEDEFS(x86_64,)
DECLARE_CONSTANTS(X86_64,)
#endif

#ifdef FRONT_ARCH_MIPS32
DECLARE_TYPEDEFS(mips32, front_)
DECLARE_CONSTANTS(MIPS32, FRONT_)
#endif

typedef struct linux_dirent64 {
	uint64_t	d_ino;
	int64_t		d_off;
	uint16_t	d_reclen;
	uint8_t		d_type;
	char		d_name[0];
} linux_dirent64_s;

typedef struct pollfd {
	int32_t		fd;
	int16_t		events;
	int16_t		revents;
} pollfd_s;

#define ____GEN_B2F_FLAG_TRANSLATOR0()
#define ____GEN_F2B_FLAG_TRANSLATOR0()

#define ____GEN_B2F_FLAG_TRANSLATOR1(flag)				\
	if (b & flag)							\
		f |= FRONT_##flag;					\
	handled |= flag;

#define ____GEN_F2B_FLAG_TRANSLATOR1(flag)				\
	if (f & FRONT_##flag)						\
		b |= flag;						\
	handled |= FRONT_##flag;

#define ____GEN_B2F_FLAG_TRANSLATOR2(a,b)				\
	____GEN_B2F_FLAG_TRANSLATOR1(a)					\
	____GEN_B2F_FLAG_TRANSLATOR1(b)

#define ____GEN_B2F_FLAG_TRANSLATOR3(a,b,c)				\
	____GEN_B2F_FLAG_TRANSLATOR2(a,b)				\
	____GEN_B2F_FLAG_TRANSLATOR1(c)

#define ____GEN_B2F_FLAG_TRANSLATOR4(a,b,c,d)				\
	____GEN_B2F_FLAG_TRANSLATOR2(a,b)				\
	____GEN_B2F_FLAG_TRANSLATOR2(c,d)

#define ____GEN_B2F_FLAG_TRANSLATOR5(a,b,c,d,e)				\
	____GEN_B2F_FLAG_TRANSLATOR3(a,b,c)				\
	____GEN_B2F_FLAG_TRANSLATOR2(d,e)

#define ____GEN_B2F_FLAG_TRANSLATOR6(a,b,c,d,e,f)			\
	____GEN_B2F_FLAG_TRANSLATOR3(a,b,c)				\
	____GEN_B2F_FLAG_TRANSLATOR3(d,e,f)

#define ____GEN_B2F_FLAG_TRANSLATOR7(a,b,c,d,e,f,g)			\
	____GEN_B2F_FLAG_TRANSLATOR4(a,b,c,d)				\
	____GEN_B2F_FLAG_TRANSLATOR3(e,f,g)

#define ____GEN_B2F_FLAG_TRANSLATOR8(a,b,c,d,e,f,g,h)			\
	____GEN_B2F_FLAG_TRANSLATOR4(a,b,c,d)				\
	____GEN_B2F_FLAG_TRANSLATOR4(e,f,g,h)

#define ____GEN_B2F_FLAG_TRANSLATOR9(a,b,c,d,e,f,g,h,i)			\
	____GEN_B2F_FLAG_TRANSLATOR5(a,b,c,d,e)				\
	____GEN_B2F_FLAG_TRANSLATOR4(f,g,h,i)

#define ____GEN_B2F_FLAG_TRANSLATOR10(a,b,c,d,e,f,g,h,i,j)		\
	____GEN_B2F_FLAG_TRANSLATOR5(a,b,c,d,e)				\
	____GEN_B2F_FLAG_TRANSLATOR5(f,g,h,i,j)

#define ____GEN_B2F_FLAG_TRANSLATOR11(a,b,c,d,e,f,g,h,i,j,k)		\
	____GEN_B2F_FLAG_TRANSLATOR6(a,b,c,d,e,f)			\
	____GEN_B2F_FLAG_TRANSLATOR5(g,h,i,j,k)

#define ____GEN_F2B_FLAG_TRANSLATOR2(a,b)				\
	____GEN_F2B_FLAG_TRANSLATOR1(a)					\
	____GEN_F2B_FLAG_TRANSLATOR1(b)

#define ____GEN_F2B_FLAG_TRANSLATOR3(a,b,c)				\
	____GEN_F2B_FLAG_TRANSLATOR2(a,b)				\
	____GEN_F2B_FLAG_TRANSLATOR1(c)

#define ____GEN_F2B_FLAG_TRANSLATOR4(a,b,c,d)				\
	____GEN_F2B_FLAG_TRANSLATOR2(a,b)				\
	____GEN_F2B_FLAG_TRANSLATOR2(c,d)

#define ____GEN_F2B_FLAG_TRANSLATOR5(a,b,c,d,e)				\
	____GEN_F2B_FLAG_TRANSLATOR3(a,b,c)				\
	____GEN_F2B_FLAG_TRANSLATOR2(d,e)

#define ____GEN_F2B_FLAG_TRANSLATOR6(a,b,c,d,e,f)			\
	____GEN_F2B_FLAG_TRANSLATOR3(a,b,c)				\
	____GEN_F2B_FLAG_TRANSLATOR3(d,e,f)

#define ____GEN_F2B_FLAG_TRANSLATOR7(a,b,c,d,e,f,g)			\
	____GEN_F2B_FLAG_TRANSLATOR4(a,b,c,d)				\
	____GEN_F2B_FLAG_TRANSLATOR3(e,f,g)

#define ____GEN_F2B_FLAG_TRANSLATOR8(a,b,c,d,e,f,g,h)			\
	____GEN_F2B_FLAG_TRANSLATOR4(a,b,c,d)				\
	____GEN_F2B_FLAG_TRANSLATOR4(e,f,g,h)

#define ____GEN_F2B_FLAG_TRANSLATOR9(a,b,c,d,e,f,g,h,i)			\
	____GEN_F2B_FLAG_TRANSLATOR5(a,b,c,d,e)				\
	____GEN_F2B_FLAG_TRANSLATOR4(f,g,h,i)

#define ____GEN_F2B_FLAG_TRANSLATOR10(a,b,c,d,e,f,g,h,i,j)		\
	____GEN_F2B_FLAG_TRANSLATOR5(a,b,c,d,e)				\
	____GEN_F2B_FLAG_TRANSLATOR5(f,g,h,i,j)

#define ____GEN_F2B_FLAG_TRANSLATOR11(a,b,c,d,e,f,g,h,i,j,k)		\
	____GEN_F2B_FLAG_TRANSLATOR6(a,b,c,d,e,f)			\
	____GEN_F2B_FLAG_TRANSLATOR5(g,h,i,j,k)

#define ___GEN_FLAG_TRANSLATOR(M, ...)					\
	M(__VA_ARGS__)

#define __GEN_B2F_FLAG_TRANSLATOR(nflags, ...)				\
	___GEN_FLAG_TRANSLATOR(CAT(____GEN_B2F_FLAG_TRANSLATOR, VA_NUM_ARGS_NOZERO(__VA_ARGS__)), __VA_ARGS__)

#define _GEN_B2F_FLAG_TRANSLATOR(...)					\
	__GEN_B2F_FLAG_TRANSLATOR(VA_NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#define __GEN_F2B_FLAG_TRANSLATOR(nflags, ...)				\
	___GEN_FLAG_TRANSLATOR(CAT(____GEN_F2B_FLAG_TRANSLATOR, VA_NUM_ARGS_NOZERO(__VA_ARGS__)), __VA_ARGS__)

#define _GEN_F2B_FLAG_TRANSLATOR(...)					\
	__GEN_F2B_FLAG_TRANSLATOR(VA_NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#define GEN_FLAG_TRANSLATOR(name, type, ...)				\
static inline front_##type b2f_##name(type b, int *allrec)		\
{									\
	type handled = 0;						\
	front_##type f = 0;						\
	_GEN_B2F_FLAG_TRANSLATOR(__VA_ARGS__)				\
	if (allrec)							\
		*allrec = (b & handled) == b;				\
	return f;							\
}									\
									\
static inline type f2b_##name(front_##type f, int *allrec)		\
{									\
	front_##type handled = 0;					\
	type b = 0;							\
	_GEN_F2B_FLAG_TRANSLATOR(__VA_ARGS__)				\
	if (allrec)							\
		*allrec = (f & handled) == f;				\
	return b;							\
}

GEN_FLAG_TRANSLATOR(mmap_flags, int_t,
	MAP_ANONYMOUS,
	MAP_DENYWRITE,
	MAP_FIXED,
	MAP_PRIVATE,
	MAP_SHARED)

GEN_FLAG_TRANSLATOR(open_flags, int_t,
	O_APPEND,
	O_CLOEXEC,
	O_CREAT,
	O_DIRECTORY,
	O_EXCL,
	O_LARGEFILE,
	O_NONBLOCK,
	O_RDONLY,
	O_RDWR,
	O_TRUNC,
	O_WRONLY)

GEN_FLAG_TRANSLATOR(poll_events, short_t,
	POLL_IN,
	POLL_OUT,
	POLL_PRI,
	POLL_RDBAND,
	POLL_RDNORM,
	POLL_WRBAND,
	POLL_WRNORM)

GEN_FLAG_TRANSLATOR(prot, int_t,
	PROT_EXEC,
	PROT_NONE,
	PROT_READ,
	PROT_WRITE)

static inline int f2b_signum(int f, int *ok)
{
	int ret, is_ok = 1;

	switch (f) {
#define SIGNAL(name)			\
	case FRONT_##name:		\
		ret = name;		\
		break;
#include "signal-list.h"
#undef SIGNAL

	default:
		is_ok = ret = 0;
	}

	if (ok)
		*ok = is_ok;
	return ret;
}

static inline int b2f_signum(int b, int *ok)
{
	int ret, is_ok = 1;

	switch (b) {
#define SIGNAL(name)			\
	case name:			\
		ret = FRONT_##name;	\
		break;
#include "signal-list.h"
#undef SIGNAL

	default:
		is_ok = ret = 0;
	}

	if (ok)
		*ok = is_ok;
	return ret;
}

#endif /* __hoodwink_types_h__ */
