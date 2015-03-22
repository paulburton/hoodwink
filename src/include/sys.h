#ifndef __hoodwink_sys_h__
#define __hoodwink_sys_h__

#include "types.h"

struct sys_state {
	void *mem_base;

	unsigned page_bits;
	unsigned long *page_bitmap;
	unsigned mmap_pfn_min, mmap_pfn_max;

	uint32_t brk, min_brk;

	front_sigaction_s sigactions[sizeof(sigset_t) * 8];
	struct sig_queue {
		_Atomic unsigned lock;
		front_siginfo_s pending[5];
		unsigned r_idx, w_idx;
	} sigs, rt_sigs;
};

#endif /* __hoodwink_sys_h__ */
