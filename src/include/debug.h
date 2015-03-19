#ifndef __hoodwink_debug_h__
#define __hoodwink_debug_h__

#ifdef DEBUG

extern unsigned debug_mask;
extern void debug_init(const char *filename);
extern void debug(const char *fmt, ...);

#else /* !DEBUG */

#define debug_mask 0
static inline void debug_init(const char *filename) {}
static inline void debug(const char *fmt, ...) {}

#endif

#define DEBUG_IN_ASM	(1 << 0)
#define DEBUG_SYSCALL	(1 << 1)
#define DEBUG_ALL	(~0)

#define debug_in_asm(...) do {				\
	if (debug_mask & DEBUG_IN_ASM)			\
		debug(__VA_ARGS__);			\
} while (0)

#define debug_syscall(...) do {				\
	if (debug_mask & DEBUG_SYSCALL)			\
		debug(__VA_ARGS__);			\
} while (0)

#endif /* __hoodwink_debug_h__ */
