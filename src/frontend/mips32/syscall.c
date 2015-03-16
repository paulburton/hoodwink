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

uint32_t frontend_syscall_arch_invoke(struct sys_state *sys, unsigned num, uint32_t args[static 8])
{
	struct mips32_state *mips = (struct mips32_state *)sys;

	switch (num) {
	case SYSCALL_NR_FRONT(set_thread_area):
		mips->cpu.ulr = args[0];
		return 0;

	default:
		return -1;
	}
}
