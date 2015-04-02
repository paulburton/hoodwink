#ifndef __hoodwink_spinlock_h__
#define __hoodwink_spinlock_h__

typedef volatile int spinlock_t;

static inline void spin_init(spinlock_t *lock)
{
	*lock = 0;
}

static inline void spin_lock(spinlock_t *lock)
{
	while (__sync_lock_test_and_set(lock, 1))
		while (*lock);
}

static inline void spin_unlock(spinlock_t *lock)
{
	__sync_lock_release(lock);
}

#endif /* __hoodwink_spinlock_h__ */
