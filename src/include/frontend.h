#ifndef __hoodwink_frontend_h__
#define __hoodwink_frontend_h__

#include "string.h"
#include "sys.h"
#include "types.h"

extern void frontend_init(const char *filename, int argc, const char *argv[]);
extern void frontend_copy(struct sys_state *dest, struct sys_state *src);
extern void frontend_loop(struct sys_state *sys);

extern void frontend_clone_thread_finish(struct sys_state *sys);

extern void frontend_deliver_rt_signal(struct sys_state *sys, front_siginfo_s *info);

#endif /* __hoodwink_frontend_h__ */
