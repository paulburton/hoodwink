#ifndef __hoodwink_sys_h__
#define __hoodwink_sys_h__

#include "types.h"

struct sys_state {
	void *mem_base;
	uint32_t brk, min_brk;
};

#endif /* __hoodwink_sys_h__ */
