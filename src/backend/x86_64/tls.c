#include "backend.h"
#include "debug.h"
#include "syscall.h"

#define ARCH_SET_FS	0x1002
#define ARCH_GET_FS	0x1003

void *backend_get_tls(void)
{
	unsigned long addr;
	int err;

	err = sys_arch_prctl(ARCH_GET_FS, (unsigned long)&addr);
	if (err) {
		debug("Failed to get FS\n");
		sys_exit(1);
	}

	return (void *)addr;
}

void backend_set_tls(void *ptr)
{
	int err;

	err = sys_arch_prctl(ARCH_SET_FS, (unsigned long)ptr);
	if (err) {
		debug("Failed to set FS\n");
		sys_exit(1);
	}
}
