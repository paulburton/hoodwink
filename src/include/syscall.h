#ifndef __hoodwink_syscall_h__
#define __hoodwink_syscall_h__

#include "config.h"
#include "sys.h"
#include "types.h"
#include "util.h"

#if defined(FRONT_ARCH_MIPS32) || defined(BACK_ARCH_MIPS32)
# include "mips32/syscall.h"
#endif
#if defined(FRONT_ARCH_X86_64) || defined(BACK_ARCH_X86_64)
# include "x86_64/syscall.h"
#endif

#define __SYSCALL_NR_FRONT(arch, name) \
	arch##_NR_##name
#define _SYSCALL_NR_FRONT(arch, name) \
	__SYSCALL_NR_FRONT(arch, name)
#define SYSCALL_NR_FRONT(name) \
	_SYSCALL_NR_FRONT(FRONT_ARCH, name)

#define SYSCALL(name, ret, ...) \
	extern ret sys_##name(__VA_ARGS__);

#include "syscall-list.h"

#undef SYSCALL

/* mark sys_exit with noreturn */
extern void sys_exit(int status) __attribute__((noreturn));

#define IS_ERROR(x) \
	((x) >= (typeof(x))-4095)

struct syscall_info {
#ifdef DEBUG
	char *name;
#endif
	unsigned nargs;
	uint32_t (*translate)(const struct sys_state *sys, uint32_t *args, void *delta);
};

#ifdef DEBUG
# define SYSCALL_NAME(n) .name = n,
#else
# define SYSCALL_NAME(n)
#endif

/* generic frontend code */
extern uint32_t frontend_syscall_invoke(const struct sys_state *sys, unsigned num, uint32_t *args, void *delta);

/* provided by the arch-specific frontend code */
extern void frontend_syscall_args(const struct sys_state *sys, unsigned nargs, uint32_t *args);

extern const struct syscall_info *frontend_syscall_arch_info(const struct sys_state *sys, unsigned num);

#endif /* __hoodwink_syscall_h__ */
