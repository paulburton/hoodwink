#ifndef __hoodwink_mm_h__
#define __hoodwink_mm_h__

#include "sys.h"
#include "types.h"

extern void mm_init(struct sys_state *sys);
extern uint32_t mm_mmap(struct sys_state *sys, uint32_t addr, uint32_t length, int prot, int flags, int fd, uint32_t offset);

static inline unsigned addr_to_pfn(struct sys_state *sys, uint32_t addr)
{
	return addr >> sys->page_bits;
}

#endif /* __hoodwink_mm_h__ */
