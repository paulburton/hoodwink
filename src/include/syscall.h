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

/* generic frontend code */
extern void frontend_syscall_invoke(struct sys_state *sys, unsigned num);

/* provided by the arch-specific frontend code */
extern void frontend_syscall_args(struct sys_state *sys, unsigned nargs, uint32_t *args);
extern void frontend_syscall_ret(struct sys_state *sys, uint32_t ret);

extern uint32_t frontend_syscall_arch_invoke(struct sys_state *sys, unsigned num, uint32_t args[static 8]);

#endif /* __hoodwink_syscall_h__ */
