#include "backend.h"
#include "debug.h"
#include "frontend.h"
#include "syscall.h"

void clone_thread_entry(struct sys_state *sys)
{
	backend_set_tls(sys);
	frontend_clone_thread_finish(sys);
	frontend_loop(sys);
}

long backend_clone(unsigned long flags, int *parent_tidptr, int *child_tidptr)
{
	struct sys_state *child_sys, *sys = backend_get_tls();
	unsigned long newsp;
	void *tmem;

	if (flags & CLONE_VM) {
		tmem = sys_mmap(NULL, 16 << 10, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (IS_ERROR(tmem)) {
			debug("Failed to mmap child stack\n");
			sys_exit(1);
		}

		child_sys = tmem + (12 << 10);
		frontend_copy(child_sys, sys);

		newsp = (unsigned long)child_sys;

		return sys_clone_vm(flags, newsp, parent_tidptr, child_tidptr, 0);
	}

	return sys_clone(flags, 0, parent_tidptr, child_tidptr, 0);
}
