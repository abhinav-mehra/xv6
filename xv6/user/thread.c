#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#define PGSIZE		4096		// bytes mapped by a page

int 
thread_create(void (*start_routine)(void*), void *arg)
{
  void *stack_ptr = 0;
  int pid = 0;
  stack_ptr = malloc(PGSIZE*2);
  if((int)stack_ptr % PGSIZE)
    stack_ptr = stack_ptr + (4096 - ((uint)stack_ptr % PGSIZE));
  pid = clone(start_routine, arg, stack_ptr);
  return pid;
}

int 
thread_join()
{
  void *stack_ptr = 0;
  int pid = 0;
  pid = join(&stack_ptr);
  free(stack_ptr);
  return pid;
}

void
lock_init(lock_t *lk)
{
  lk->locked = 0;
}

void
lock_acquire(lock_t *lk)
{
  // The xchg is atomic.
  // It also serializes, so that reads after acquire are not
  // reordered before it. 
  while(xchg(&lk->locked, 1) != 0)

    ;
}

void
lock_release(lock_t *lk)
{
  // The xchg serializes, so that reads before release are 
  // not reordered after it.  The 1996 PentiumPro manual (Volume 3,
  // 7.2) says reads can be carried out speculatively and in
  // any order, which implies we need to serialize here.
  // But the 2007 Intel 64 Architecture Memory Ordering White
  // Paper says that Intel 64 and IA-32 will not move a load
  // after a store. So lock->locked = 0 would work here.
  // The xchg being asm volatile ensures gcc emits it after
  // the above assignments (and after the critical section).
  xchg(&lk->locked, 0);

}
