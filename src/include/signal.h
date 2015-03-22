#ifndef __hoodwink_signal_h__
#define __hoodwink_signal_h__

#include "sys.h"

extern void signal_init(struct sys_state *sys);
extern void signal_enqueue(struct sys_state *sys, const front_siginfo_s *info);
extern void signal_dequeue(struct sys_state *sys, front_siginfo_s *info);
extern unsigned signal_pending(struct sys_state *sys);

#endif /* __hoodwink_signal_h__ */
