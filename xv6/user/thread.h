#ifndef _THREAD_H_
#define _THREAD_H

// Mutual exclusion lock.
typedef struct lock {
  uint locked;       // Is the lock held?
} lock_t;

int thread_create(void (*start_routine)(void*), void *arg);
int thread_join();
void lock_init(lock_t *);
void lock_acquire(lock_t *);
void lock_release(lock_t *);

#endif // _SPINLOCK_H_
