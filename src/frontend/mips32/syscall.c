#include "backend.h"
#include "debug.h"
#include "mips32.h"
#include "sys.h"
#include "syscall.h"
#include "util.h"

void frontend_syscall_args(struct sys_state *sys, unsigned nargs, uint32_t *args)
{
	struct mips32_state *mips = (struct mips32_state *)sys;
	int i;

	/* read first 4 args from registers */
	for (i = 0; i < min(nargs, 4); i++)
		args[i] = mips->cpu.gpr[4 + i];

	/* read remaining args from the stack */
	for (i = 4; i < nargs; i++)
		args[i] = ((uint32_t *)(mips->sys.mem_base + mips->cpu.gpr[29]))[i];
}

void frontend_syscall_ret(struct sys_state *sys, uint32_t ret)
{
	struct mips32_state *mips = (struct mips32_state *)sys;

	mips->cpu.gpr[2] = ret;
	mips->cpu.gpr[7] = IS_ERROR(ret);
}

static uint32_t translate_sys_clone(struct sys_state *sys, uint32_t *args)
{
	int parent_tid, *parent_tidptr;
	int child_tid, *child_tidptr;
	long ret;

	parent_tidptr = args[2] ? &parent_tid : NULL;
	child_tidptr = args[4] ? &child_tid : NULL;

	ret = backend_clone(args[0], args[1], parent_tidptr, child_tidptr, args[3]);

	if (parent_tidptr)
		*(front_int_t *)(sys->mem_base + args[2]) = parent_tid;
	if (child_tidptr)
		*(front_int_t *)(sys->mem_base + args[4]) = child_tid;

	return ret;
}

static const struct syscall_info info_clone = {
	SYSCALL_NAME("clone")
	.nargs = 5,
	.translate = translate_sys_clone,
};

static uint32_t translate_sys_set_thread_area(struct sys_state *sys, uint32_t *args)
{
	struct mips32_state *mips = (struct mips32_state *)sys;
	mips->cpu.ulr = args[0];
	return 0;
}

static const struct syscall_info info_set_thread_area = {
	SYSCALL_NAME("set_thread_area")
	.nargs = 1,
	.translate = translate_sys_set_thread_area,
};

const struct syscall_info *frontend_syscall_arch_info(struct sys_state *sys, unsigned num)
{
	switch (num) {
	case SYSCALL_NR_FRONT(clone):
		return &info_clone;

	case SYSCALL_NR_FRONT(set_thread_area):
		return &info_set_thread_area;

	default:
		return NULL;
	}
}
