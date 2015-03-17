#ifndef __hoodwink_sys_h__
#define __hoodwink_sys_h__

#include "types.h"

struct sys_state {
	void *mem_base;

	unsigned page_bits;
	unsigned long *page_bitmap;
	unsigned mmap_pfn_min, mmap_pfn_max;

	uint32_t brk, min_brk;
};

#endif /* __hoodwink_sys_h__ */
