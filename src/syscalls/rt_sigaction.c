#include "backend.h"
#include "debug.h"
#include "signal.h"
#include "string.h"
#include "syscall.h"
#include "types.h"

static void rt_signal_handler(int signum, siginfo_s *info, ucontext_s *uc)
{
	struct sys_state *sys = backend_get_tls();
	int front_signum, front_signum_ok;
	front_siginfo_s f_info = { 0 };
       
	front_signum = b2f_signum(signum, &front_signum_ok);
	if (!front_signum_ok) {
		debug("Unrecognised backend signal %d\n", signum);
		return;
	}

	f_info.si_signo = front_signum;
	f_info.si_code = info->si_code;
	f_info.si_errno = info->si_errno;

	switch (signum) {
	case SIGCHLD:
		f_info._sifields._sigchld._pid = info->_sifields._sigchld._pid;
		f_info._sifields._sigchld._uid = info->_sifields._sigchld._uid;
		f_info._sifields._sigchld._utime = info->_sifields._sigchld._utime;
		f_info._sifields._sigchld._stime = info->_sifields._sigchld._stime;

		if (info->si_code == 1 /* CLD_EXITED */)
			f_info._sifields._sigchld._status = info->_sifields._sigchld._status;
		else
			f_info._sifields._sigchld._status = b2f_signum(info->_sifields._sigchld._status, NULL);
		break;
	}

	signal_enqueue(sys, &f_info);
}

uint32_t translate_sys_rt_sigaction(struct sys_state *sys, uint32_t *args)
{
	front_sigaction_s *f_act, *f_oldact;
	sigaction_s b_act, *pb_act = NULL;
	int front_signum, back_signum, back_signum_ok;

	front_signum = args[0];
	back_signum = f2b_signum(front_signum, &back_signum_ok);

	if (!back_signum_ok) {
		debug("Unrecognised signum %d\n", front_signum);
		return -FRONT_EINVAL;
	}

	if (args[1]) {
		f_act = sys->mem_base + args[1];
		sys->sigactions[front_signum] = *f_act;

		pb_act = &b_act;
		memset(&b_act, 0, sizeof(b_act));
		b_act.sa_flags = SA_SIGINFO | SA_RESTORER;
		b_act.sa_restorer = (uint64_t)&sys_rt_sigreturn;

		if (f_act->sa_handler == 0 /* SIGDFL */)
			b_act.sa_handler = 0;
		else if (f_act->sa_handler == 1 /* SIGIGN */)
			b_act.sa_handler = 1;
		else
			b_act.sa_handler = (uint64_t)&rt_signal_handler;
	}

	if (args[2]) {
		f_oldact = sys->mem_base + args[2];
		*f_oldact = sys->sigactions[front_signum];
	}

	return sys_rt_sigaction(back_signum, pb_act, NULL, sizeof(sigset_t));
}
