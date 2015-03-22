#include "syscall.h"

static unsigned count_ptr_array(uint32_t *arr)
{
	unsigned count = 0;

	while (*arr++)
		count++;

	return count;
}

uint32_t translate_sys_execve(struct sys_state *sys, uint32_t *args)
{
	uint32_t *f_argv = sys->mem_base + args[1];
	uint32_t *f_envp = sys->mem_base + args[2];
	unsigned nargv = count_ptr_array(f_argv);
	unsigned nenvp = count_ptr_array(f_envp);
	char *argv[nargv + 1], *envp[nenvp + 1];
	unsigned i;

	for (i = 0; i < nargv; i++)
		argv[i] = sys->mem_base + f_argv[i];
	argv[i] = NULL;

	for (i = 0; i < nenvp; i++)
		envp[i] = sys->mem_base + f_envp[i];
	envp[i] = NULL;

	return sys_execve(sys->mem_base + args[0], argv, envp);
}
