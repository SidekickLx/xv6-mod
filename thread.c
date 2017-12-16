#include "types.h"
#include "stat.h"
#include "user.h"
#include "x86.h"
#define PGSIZE 4096

int 
spinlock_init(spinlock_t* lock){
  lock->locked = 0;
  return 0;
}

void
spinlock_acquire(spinlock_t *lock){
  while(xchg(&(lock->locked), 1) == 1);
}

void 
spinlock_release(spinlock_t *lock){
  xchg(&lock->locked, 0);
}

int
qlock_init(qlock_t *lock, uint size){
  lock->qsize = size;
  lock->flag = (int*)malloc(sizeof(int) * size);
  lock->tail = 0;
  lock->flag[0] = 1;
  return 0;
}

void
qlock_acquire(qlock_t *lock, int slot){
  while(!(lock->flag[slot]));
}

void
qlock_release(qlock_t *lock, int slot){
  lock->flag[slot] = 0;
  lock->flag[(slot+1) % lock->qsize] = 1;
  lock -> tail ++; 
}

int
seqlock_init(seqlock_t *lock){
  lock->seq = 0;
  spinlock_init(&(lock->spinlock));
  return 0;
}

void
seqlock_writer_aquire(seqlock_t *lock){
    lock->seq ++;
    spinlock_acquire(&(lock->spinlock));
}

void
seqlock_writer_release(seqlock_t *lock){
    lock->seq ++;
    spinlock_release(&(lock->spinlock));
}

int
seqlock_reader_aquire(seqlock_t *lock){
  while(((lock->seq) % 2)) ;
  return lock->seq;
}

int
seqlock_reader_retry(seqlock_t *lock, int startseq){
  if(lock->seq != startseq) return 1;
  else return 0;
}



int
thread_create(void (start_routine)(void*), void *arg){
  void *stack = malloc(PGSIZE);
  if(!stack){
    printf(1, "error!");
    exit();
  }
  if((uint)stack % PGSIZE)
    stack = stack + (PGSIZE - (uint)stack % PGSIZE);

  *((uint*)(stack + PGSIZE - 4)) = (uint)arg;
  *((uint*)(stack +  PGSIZE - 2 * 4)) = (uint)start_routine;
  return clone(stack, PGSIZE);
}
