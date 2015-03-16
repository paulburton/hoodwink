#ifndef __hoodwink_debug_h__
#define __hoodwink_debug_h__

#ifdef DEBUG

extern void debug_init(const char *filename);
extern void debug(const char *fmt, ...);

#else /* !DEBUG */

static inline void debug_init(const char *filename) {}
static inline void debug(const char *fmt, ...) {}

#endif

#endif /* __hoodwink_debug_h__ */
