#include "mm.h"
#include "syscall.h"

uint32_t translate_sys_mmap(struct sys_state *sys, uint32_t *args)
{
	return mm_mmap(sys, args[0], args[1], args[2], f2b_mmap_flags(args[3]), args[4], args[5]);
}
