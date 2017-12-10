#include "types.h"
#include "stat.h"
#include "user.h"
#include "x86.h"
#define PGSIZE 4096

int 
lock_init(lock_t* lock){
  lock->locked = 0;
  return 0;
}

void
lock_acquire(lock_t *lock){
  while( xchg(&lock->locked, 1) != 0);
}

void 
lock_release(lock_t *lock){
  xchg(&lock->locked, 0);
}

int
thread_create(void (*start_routine)(void*), void *arg){
  void *stack = malloc(PGSIZE);
  if(!stack){
    printf(1, "error!");
    exit();
  }
  if((uint)stack % PGSIZE)
    stack = stack + (PGSIZE - (uint)stack % PGSIZE);

  *((uint*)(stack + PGSIZE - 4)) = (uint)arg;
  *((uint*)(stack +  PGSIZE - 2 * 4)) = (uint)start_routine;

  return clone(stack, PGSIZE );
}
