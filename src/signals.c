#include "debug.h"
#include "mm.h"
#include "signals.h"
#include "string.h"
#include "sys.h"
#include "syscall.h"

static void segv_handler(int signum, void *info, void *uc)
{
	debug("SEGV!\n");
}

void signals_init(struct sys_state *sys)
{
	sigaction_s sa;
	int err;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = (uint64_t)&segv_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTORER;

	err = sys_rt_sigaction(SIGSEGV, &sa, NULL, sizeof(sigset_t));
	if (err) {
		debug("Failed to set SIGSEGV handler: %d\n", err);
		sys_exit(1);
	}
}
