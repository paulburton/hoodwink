#include "debug.h"
#include "frontend.h"
#include "mips32.h"
#include "types.h"

void frontend_deliver_rt_signal(struct sys_state *sys, front_siginfo_s *info)
{
	struct mips32_state *mips = (void *)sys;
	struct mips32_rt_sigframe *frame;
	struct mips32_ucontext *uc;
	struct mips32_sigcontext *sc;
	int i;

	debug_signal("%s %d\n", __func__, info->si_signo);

	frame = sys->mem_base + mips->cpu.gpr[29] - sizeof(*frame);
	frame->rs_info = *info;

	uc = &frame->rs_uc;
	uc->uc_flags = 0;
	uc->uc_link = 0;

	sc = &uc->uc_mcontext;
	sc->sc_regmask = 0;
	sc->sc_status = 0;
	sc->sc_pc = mips->cpu.pc;

	for (i = 0; i < 32; i++)
		sc->sc_regs[i] = mips->cpu.gpr[i];

	for (i = 0; i < 32; i++)
		sc->sc_fpregs[i] = mips->cpu.fpr[i];

	mips->cpu.gpr[4] = info->si_signo;
	mips->cpu.gpr[5] = (void *)&frame->rs_info - sys->mem_base;
	mips->cpu.gpr[6] = (void *)&frame->rs_uc - sys->mem_base;
	mips->cpu.gpr[29] = (void *)frame - sys->mem_base;
	mips->cpu.gpr[31] = frontend_vdso_entry(sys, VDSO_RT_SIGRETURN);
	mips->cpu.pc = mips->cpu.gpr[25] = sys->sigactions[info->si_signo].sa_handler;
}

void frontend_rt_sigreturn(const struct mips32_state *mips, struct mips32_delta *delta)
{
	const struct sys_state *sys = &mips->sys;
	struct mips32_rt_sigframe *frame = sys->mem_base + mips->cpu.gpr[29];
	struct mips32_ucontext *uc = &frame->rs_uc;
	struct mips32_sigcontext *sc = &uc->uc_mcontext;
	int i;

	debug_signal("%s %d\n", __func__, frame->rs_info.si_signo);

	for (i = 0; i < 32; i++)
		mips32_delta_set(delta, GPR0 + i, sc->sc_regs[i]);

	for (i = 0; i < 32; i++)
		mips32_delta_set(delta, FPR0 + i, sc->sc_fpregs[i]);

	delta->next_pc = sc->sc_pc;
}
