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

#define DECLARE_TYPEDEFS(arch, prefix)					\
	typedef arch##_int_t			prefix##int_t;		\
	typedef arch##_gid_t			prefix##gid_t;		\
	typedef arch##_mode_t			prefix##mode_t;		\
	typedef arch##_off_t			prefix##off_t;		\
	typedef arch##_pid_t			prefix##pid_t;		\
	typedef arch##_sigset_t			prefix##sigset_t;	\
	typedef arch##_size_t			prefix##size_t;		\
	typedef arch##_ssize_t			prefix##ssize_t;	\
	typedef arch##_uid_t			prefix##uid_t;		\
	typedef struct arch##_iovec		prefix##iovec_s;	\
	typedef struct arch##_sigaction		prefix##sigaction_s;	\
	typedef struct arch##_stat		prefix##stat_s;		\
	typedef struct arch##_stat64		prefix##stat64_s;	\
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
	static const int prefix##SA_SIGINFO = arch##_SA_SIGINFO;	\
	static const int prefix##SIGSEGV = arch##_SIGSEGV;

#ifdef FRONT_ARCH_MIPS32
DECLARE_TYPEDEFS(mips32, front_)
DECLARE_CONSTANTS(MIPS32, FRONT_)
#endif

#ifdef BACK_ARCH_X86_64
DECLARE_TYPEDEFS(x86_64,)
DECLARE_CONSTANTS(X86_64,)
#endif

#define _____GEN_FLAG_TRANSLATOR(flag)					\
	if (f & FRONT_##flag)						\
		b |= flag;						\
	handled |= FRONT_##flag;

#define ____GEN_FLAG_TRANSLATOR0(a,b,c,d)

#define ____GEN_FLAG_TRANSLATOR1(a,b,c,d)				\
	_____GEN_FLAG_TRANSLATOR(d)

#define ____GEN_FLAG_TRANSLATOR2(a,b,c,d)				\
	_____GEN_FLAG_TRANSLATOR(c)					\
	_____GEN_FLAG_TRANSLATOR(d)

#define ____GEN_FLAG_TRANSLATOR3(a,b,c,d)				\
	_____GEN_FLAG_TRANSLATOR(b)					\
	_____GEN_FLAG_TRANSLATOR(c)					\
	_____GEN_FLAG_TRANSLATOR(d)

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

#endif /* __hoodwink_types_h__ */
