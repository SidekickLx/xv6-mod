#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "proc.h"
#include "x86.h"

typedef struct spinlock {
    uint locked;       // Is the lock held?
  
    // For debugging:
    char *name;        // Name of lock.
    struct cpu *cpu;   // The cpu holding the lock.
    uint pcs[10];      // The call stack (an array of program counters)
                       // that locked the lock.
  }lock_t;



void
start_routine(void *ptr){

}

int
thread_create(void *(*start_routine)(void*), void *arg){

}

void 
lock_init(lock_t* lock){

}

void
lock_acquire(lock_t *lock){

}

void 
lock_release(lock_t *lock){

}