#include "syscall.h"

uint32_t translate_sys_writev(struct sys_state *sys, uint32_t *args)
{
	front_iovec_s *fvec = sys->mem_base + args[1];
	iovec_s bvec[args[2]];

	for (i = 0; i < args[2]; i++) {
		bvec[i].iov_base = (uintptr_t)(sys->mem_base + fvec[i].iov_base);
		bvec[i].iov_len = fvec[i].iov_len;
	}

	return sys_writev(args[0], bvec, args[2]);
}
