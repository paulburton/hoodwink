#include "backend.h"
#include "debug.h"
#include "frontend.h"
#include "mips32.h"
#include "string.h"
#include "sys.h"
#include "syscall.h"
#include "util.h"

void frontend_syscall_args(const struct sys_state *sys, unsigned nargs, uint32_t *args)
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

void frontend_clone_thread_finish(struct sys_state *sys)
{
	struct mips32_state *mips = (struct mips32_state *)sys;

	/* skip over the clone syscall instruction */
	mips->cpu.pc += 4;

	if (mips->cpu.gpr[5])
		mips->cpu.gpr[29] = mips->cpu.gpr[5];

	if (mips->cpu.gpr[4] & CLONE_SETTLS)
		mips->cpu.ulr = mips->cpu.gpr[7];

	/* set syscall results */
	mips->cpu.gpr[2] = 0;
	mips->cpu.gpr[7] = 0;
}

static uint32_t translate_sys_clone(const struct sys_state *sys, uint32_t *args, void *_delta)
{
	int *parent_tidptr, *child_tidptr;
	int signum, signum_ok;
	unsigned long flags;

	flags = args[0] & ~0xfful;
	flags &= ~CLONE_SETTLS;

	signum = args[0] & 0xff;
	if (signum) {
		flags |= f2b_signum(signum, &signum_ok);
		if (!signum_ok) {
			debug("Unrecognised signal number %d\n", signum);
			return -FRONT_EINVAL;
		}
	}

	parent_tidptr = args[2] ? sys->mem_base + args[2] : NULL;
	child_tidptr = args[4] ? sys->mem_base + args[4] : NULL;

	return backend_clone(flags, parent_tidptr, child_tidptr);
}

static const struct syscall_info info_clone = {
	SYSCALL_NAME("clone")
	.nargs = 5,
	.translate = translate_sys_clone,
};

static uint32_t translate_rt_sigreturn(const struct sys_state *sys, uint32_t *args, void *_delta)
{
	struct mips32_state *mips = (void *)sys;
	struct mips32_delta *delta = _delta;
	frontend_rt_sigreturn(mips, delta);
	return 0;
}

static const struct syscall_info info_rt_sigreturn = {
	SYSCALL_NAME("rt_sigreturn")
	.nargs = 0,
	.translate = translate_rt_sigreturn,
};

static uint32_t translate_sys_set_thread_area(const struct sys_state *sys, uint32_t *args, void *_delta)
{
	struct mips32_delta *delta = _delta;
	mips32_delta_set(delta, ULR, args[0]);
	return 0;
}

static const struct syscall_info info_set_thread_area = {
	SYSCALL_NAME("set_thread_area")
	.nargs = 1,
	.translate = translate_sys_set_thread_area,
};

static uint32_t translate_sys_syscall(const struct sys_state *sys, uint32_t *args, void *_delta)
{
	unsigned num = args[0];

	return frontend_syscall_invoke(sys, num, &args[1], _delta);
}

static const struct syscall_info info_syscall = {
	SYSCALL_NAME("syscall")
	.nargs = 7,
	.translate = translate_sys_syscall,
};

const struct syscall_info *frontend_syscall_arch_info(const struct sys_state *sys, unsigned num)
{
	switch (num) {
	case SYSCALL_NR_FRONT(clone):
		return &info_clone;

	case SYSCALL_NR_FRONT(rt_sigreturn):
		return &info_rt_sigreturn;

	case SYSCALL_NR_FRONT(set_thread_area):
		return &info_set_thread_area;

	case SYSCALL_NR_FRONT(syscall):
		return &info_syscall;

	default:
		return NULL;
	}
}
