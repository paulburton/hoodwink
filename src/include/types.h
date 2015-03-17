#ifndef __hoodwink_types_h__
#define __hoodwink_types_h__

#include <stdint.h>

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

/* prot_t */
#define PROT_NONE	0x0
#define PROT_READ	0x1
#define PROT_WRITE	0x2
#define PROT_EXEC	0x4

/* mmap flags */
#define MAP_SHARED	0x01
#define MAP_PRIVATE	0x02
#define MAP_FIXED	0x10

#define DECLARE_TYPEDEFS(arch, prefix)					\
	typedef arch##_mode_t			prefix##mode_t;		\
	typedef arch##_off_t			prefix##off_t;		\
	typedef arch##_pid_t			prefix##pid_t;		\
	typedef arch##_size_t			prefix##size_t;		\
	typedef arch##_ssize_t			prefix##ssize_t;	\
	typedef struct arch##_iovec		prefix##iovec_s;	\
	typedef struct arch##_stat		prefix##stat_s;		\
	typedef struct arch##_stat64		prefix##stat64_s;	\
	typedef struct arch##_utsname		prefix##utsname_s;

#define DECLARE_CONSTANTS(arch, prefix)					\
	static const int prefix##MAP_ANONYMOUS = arch##_MAP_ANONYMOUS;	\
	static const int prefix##O_RDONLY = arch##_O_RDONLY;		\
	static const int prefix##O_WRONLY = arch##_O_WRONLY;		\
	static const int prefix##O_RDWR = arch##_O_RDWR;		\
	static const int prefix##O_CREAT = arch##_O_CREAT;		\
	static const int prefix##O_TRUNC = arch##_O_TRUNC;

#ifdef FRONT_ARCH_MIPS32
DECLARE_TYPEDEFS(mips32, front_)
DECLARE_CONSTANTS(MIPS32, FRONT_)
#endif

#ifdef BACK_ARCH_X86_64
DECLARE_TYPEDEFS(x86_64,)
DECLARE_CONSTANTS(X86_64,)
#endif

static inline int f2b_mmap_flags(int f)
{
	int b = 0;

	if (f & MAP_SHARED)
		b |= MAP_SHARED;
	if (f & MAP_PRIVATE)
		b |= MAP_PRIVATE;
	if (f & MAP_FIXED)
		b |= MAP_FIXED;
	if (f & FRONT_MAP_ANONYMOUS)
		b |= MAP_ANONYMOUS;

	return b;
}

#endif /* __hoodwink_types_h__ */
