#include "debug.h"
#include "mm.h"
#include "string.h"
#include "syscall.h"
#include "util.h"

#define NUM_OFFSET SYSCALL_NR_FRONT(_min)

#define SYSCALL(_name, _ret, ...)							\
__attribute__((weak))									\
uint32_t translate_sys_##_name(const struct sys_state *sys, uint32_t *args, void *delta)\
{											\
	return -FRONT_EINVAL;								\
}

#include "syscall-list.h"
#undef SYSCALL

#define SYSCALL(_name, _ret, ...) [SYSCALL_NR_FRONT(_name) - NUM_OFFSET] = {		\
	SYSCALL_NAME(#_name)								\
	.nargs = VA_NUM_ARGS(__VA_ARGS__),						\
	.translate = translate_sys_##_name,						\
},

static const struct syscall_info syscall_info[] = {
#include "syscall-list.h"
};

#undef SYSCALL

uint32_t frontend_syscall_invoke(const struct sys_state *sys, unsigned num, uint32_t *args, void *delta)
{
	const struct syscall_info *info;
	uint32_t _args[8], ret;
	unsigned nargs;
	int i;

	if ((num - NUM_OFFSET) < ARRAY_SIZE(syscall_info)) {
		info = &syscall_info[num - NUM_OFFSET];
		if (!info->translate)
			info = NULL;
	} else {
		info = NULL;
	}

	if (!info)
		info = frontend_syscall_arch_info(sys, num);

	nargs = info ? info->nargs : 0;

	if (!args) {
		args = _args;
		frontend_syscall_args(sys, nargs, args);
	}

#ifdef DEBUG
	debug("syscall %u %s(", num, info ? info->name : "UNKNOWN");
	for (i = 0; i < nargs; i++)
		debug("%s0x%x", i ? ", " : "", args[i]);
	debug(")");
#else
	(void)i;
#endif

	ret = info ? info->translate(sys, args, delta) : -FRONT_EINVAL;
	debug(" = %d (0x%x)\n", ret, ret);
	return ret;
}
