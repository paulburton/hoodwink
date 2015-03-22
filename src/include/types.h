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

#define IOC_NONE		CAT(BACK_ARCH, _IOC_NONE)
#define IOC_READ		CAT(BACK_ARCH, _IOC_READ)
#define IOC_WRITE		CAT(BACK_ARCH, _IOC_WRITE)
#define IOC_SIZEBITS		CAT(BACK_ARCH, _IOC_SIZEBITS)
#define IOC_DIRBITS		CAT(BACK_ARCH, _IOC_DIRBITS)

#define FRONT_IOC_NONE		CAT(FRONT_ARCH, _IOC_NONE)
#define FRONT_IOC_READ		CAT(FRONT_ARCH, _IOC_READ)
#define FRONT_IOC_WRITE		CAT(FRONT_ARCH, _IOC_WRITE)
#define FRONT_IOC_SIZEBITS	CAT(FRONT_ARCH, _IOC_SIZEBITS)
#define FRONT_IOC_DIRBITS	CAT(FRONT_ARCH, _IOC_DIRBITS)

#define DECLARE_TYPEDEFS(arch, prefix)					\
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
	typedef struct arch##_rt_sigframe	prefix##rt_sigframe_s;	\
	typedef struct arch##_sigaction		prefix##sigaction_s;	\
	typedef struct arch##_sigaltstack	prefix##sigaltstack_s;	\
	typedef struct arch##_sigcontext	prefix##sigcontext_s;	\
	typedef struct arch##_siginfo		prefix##siginfo_s;	\
	typedef struct arch##_stat		prefix##stat_s;		\
	typedef struct arch##_stat64		prefix##stat64_s;	\
	typedef struct arch##_termios		prefix##termios_s;	\
	typedef struct arch##_timespec		prefix##timespec_s;	\
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
	static const int prefix##O_TRUNC = arch##_O_TRUNC;		\
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

#define _____GEN_FLAG_TRANSLATOR(flag)					\
	if (f & FRONT_##flag)						\
		b |= flag;						\
	handled |= FRONT_##flag;

#define ____GEN_FLAG_TRANSLATOR0()

#define ____GEN_FLAG_TRANSLATOR1(a)					\
	_____GEN_FLAG_TRANSLATOR(a)

#define ____GEN_FLAG_TRANSLATOR2(a)					\
	_____GEN_FLAG_TRANSLATOR(a)					\
	_____GEN_FLAG_TRANSLATOR(b)

#define ____GEN_FLAG_TRANSLATOR3(a,b,c)					\
	_____GEN_FLAG_TRANSLATOR(a)					\
	_____GEN_FLAG_TRANSLATOR(b)					\
	_____GEN_FLAG_TRANSLATOR(c)

#define ____GEN_FLAG_TRANSLATOR4(a,b,c,d)				\
	_____GEN_FLAG_TRANSLATOR(a)					\
	_____GEN_FLAG_TRANSLATOR(b)					\
	_____GEN_FLAG_TRANSLATOR(c)					\
	_____GEN_FLAG_TRANSLATOR(d)

#define ____GEN_FLAG_TRANSLATOR5(a,b,c,d,e)				\
	_____GEN_FLAG_TRANSLATOR(a)					\
	_____GEN_FLAG_TRANSLATOR(b)					\
	_____GEN_FLAG_TRANSLATOR(c)					\
	_____GEN_FLAG_TRANSLATOR(d)					\
	_____GEN_FLAG_TRANSLATOR(e)

#define ____GEN_FLAG_TRANSLATOR6(a,b,c,d,e,f)				\
	_____GEN_FLAG_TRANSLATOR(a)					\
	_____GEN_FLAG_TRANSLATOR(b)					\
	_____GEN_FLAG_TRANSLATOR(c)					\
	_____GEN_FLAG_TRANSLATOR(d)					\
	_____GEN_FLAG_TRANSLATOR(e)					\
	_____GEN_FLAG_TRANSLATOR(f)

#define ____GEN_FLAG_TRANSLATOR7(a,b,c,d,e,f,g)				\
	_____GEN_FLAG_TRANSLATOR(a)					\
	_____GEN_FLAG_TRANSLATOR(b)					\
	_____GEN_FLAG_TRANSLATOR(c)					\
	_____GEN_FLAG_TRANSLATOR(d)					\
	_____GEN_FLAG_TRANSLATOR(e)					\
	_____GEN_FLAG_TRANSLATOR(f)					\
	_____GEN_FLAG_TRANSLATOR(g)

#define ____GEN_FLAG_TRANSLATOR8(a,b,c,d,e,f,g,h)			\
	_____GEN_FLAG_TRANSLATOR(a)					\
	_____GEN_FLAG_TRANSLATOR(b)					\
	_____GEN_FLAG_TRANSLATOR(c)					\
	_____GEN_FLAG_TRANSLATOR(d)					\
	_____GEN_FLAG_TRANSLATOR(e)					\
	_____GEN_FLAG_TRANSLATOR(f)					\
	_____GEN_FLAG_TRANSLATOR(g)					\
	_____GEN_FLAG_TRANSLATOR(h)

#define ___GEN_FLAG_TRANSLATOR(M, ...)					\
	M(__VA_ARGS__)

#define __GEN_FLAG_TRANSLATOR(nflags, ...)				\
	___GEN_FLAG_TRANSLATOR(CAT(____GEN_FLAG_TRANSLATOR, VA_NUM_ARGS_NOZERO(__VA_ARGS__)), __VA_ARGS__)

#define _GEN_FLAG_TRANSLATOR(...)					\
	__GEN_FLAG_TRANSLATOR(VA_NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#define GEN_FLAG_TRANSLATOR(name, type, ...)				\
static inline type f2b_##name(front_##type f, int *allrec)		\
{									\
	front_##type handled = 0;					\
	type b = 0;							\
	_GEN_FLAG_TRANSLATOR(__VA_ARGS__)				\
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
