#include "debug.h"
#include "mm.h"
#include "string.h"
#include "syscall.h"
#include "util.h"

#define NUM_OFFSET SYSCALL_NR_FRONT(_min)

#define SYSCALL(_name, _ret, ...)						\
__attribute__((weak))								\
uint32_t translate_sys_##_name(struct sys_state *sys, uint32_t *args)		\
{										\
	return -FRONT_EINVAL;							\
}

#include "syscall-list.h"
#undef SYSCALL

#define SYSCALL(_name, _ret, ...) [SYSCALL_NR_FRONT(_name) - NUM_OFFSET] = {	\
	SYSCALL_NAME(#_name)							\
	.nargs = VA_NUM_ARGS(__VA_ARGS__),					\
	.translate = translate_sys_##_name,					\
},

static const struct syscall_info syscall_info[] = {
#include "syscall-list.h"
};

#undef SYSCALL

void frontend_syscall_invoke(struct sys_state *sys, unsigned num)
{
	const struct syscall_info *info;
	uint32_t args[8], ret;
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
	frontend_syscall_args(sys, nargs, args);

#ifdef DEBUG
	debug("syscall %u %s(", num, info ? info->name : "UNKNOWN");
	for (i = 0; i < nargs; i++)
		debug("%s0x%x", i ? ", " : "", args[i]);
	debug(")\n");
#else
	(void)i;
#endif

	ret = info ? info->translate(sys, args) : -FRONT_EINVAL;
	frontend_syscall_ret(sys, ret);
}
