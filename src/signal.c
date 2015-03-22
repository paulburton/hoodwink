#include "debug.h"
#include "syscall.h"
#include "types.h"
#include "util.h"

static void signal_queue_init(struct sig_queue *q)
{
	q->r_idx = q->w_idx = 0;
	q->lock = 0;
}

static void signal_queue_lock(struct sig_queue *q)
{
	q->lock++;
}

static void signal_queue_unlock(struct sig_queue *q)
{
	q->lock--;
}

static void signal_queue_enqueue(struct sig_queue *q, const front_siginfo_s *info)
{
	unsigned idx;

	signal_queue_lock(q);

	idx = q->w_idx++;
	q->w_idx %= ARRAY_SIZE(q->pending);

	q->pending[idx] = *info;

	signal_queue_unlock(q);
}

static int signal_queue_dequeue(struct sig_queue *q, front_siginfo_s *info)
{
	unsigned idx;

	signal_queue_lock(q);

	if (q->r_idx == q->w_idx) {
		signal_queue_unlock(q);
		return 0;
	}

	idx = q->r_idx++;
	q->r_idx %= ARRAY_SIZE(q->pending);

	*info = q->pending[idx];

	signal_queue_unlock(q);
	return 1;
}

void signal_init(struct sys_state *sys)
{
	signal_queue_init(&sys->sigs);
	signal_queue_init(&sys->rt_sigs);
}

void signal_enqueue(struct sys_state *sys, const front_siginfo_s *info)
{
	signal_queue_enqueue(&sys->sigs, info);
}

void signal_dequeue(struct sys_state *sys, front_siginfo_s *info)
{
	if (signal_queue_dequeue(&sys->sigs, info))
		return;
	if (signal_queue_dequeue(&sys->rt_sigs, info))
		return;

	debug("%s with no signals pending!\n", __func__);
}

unsigned signal_pending(struct sys_state *sys)
{
	if (sys->sigs.r_idx != sys->sigs.w_idx)
		return 1;
	if (sys->rt_sigs.r_idx != sys->rt_sigs.w_idx)
		return 1;
	return 0;
}
