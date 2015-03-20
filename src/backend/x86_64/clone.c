#include "backend.h"
#include "syscall.h"

long backend_clone(unsigned long clone_flags, unsigned long newsp,
		   int *parent_tidptr, int *child_tidptr, int tls_val)
{
	return sys_clone(clone_flags, newsp, parent_tidptr, child_tidptr, tls_val);
}
