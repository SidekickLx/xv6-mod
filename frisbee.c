#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

	// printf(1, "=================\n");
	// printf(1, "info %p\n", info);
	// printf(1, "pass: %d\n", *(uint*)(info));
	// printf(1, "thread_number: %d\n", *(uint*)(info+4));
	// printf(1, "threadid: %d\n", *(uint*)(info+8));
	// printf(1, "spinlock: %p\n", *(uint*)(info+12));
	// printf(1, "=================\n");


// 	uint pass;
// 	uint thread_number;
// 	uint threadid;
// 	spinlock_t *spin_lock;
// 	or qlock_t  *q_lock;
// 	or seqlock_t *seq_lock;


static uint CURRENT_PASS = 1;
static uint NEXT = 0;
/*
void frisbee1(void* info){
	int crt_ps;
	uint pass = *(uint*)(info);
	uint thread_number = *(uint*)(info+4);
	uint threadid = *(uint*)(info+8);
	spinlock_t *spin_lock = *(spinlock_t**)(info+12);
	do{
		if(threadid == NEXT){
			spinlock_acquire(spin_lock);
			crt_ps = CURRENT_PASS;
			CURRENT_PASS = CURRENT_PASS + 1;
			if(thread_number == threadid + 1) NEXT = 0;
			else NEXT = NEXT + 1;
			spinlock_release(spin_lock);
			if(threadid+1 == thread_number)
				printf(1, "Pass number no: %d, Thread %d is passing the token to thread %d\n", crt_ps, threadid, NEXT);
			else
				printf(1, "Pass number no: %d, Thread %d is passing the token to thread %d\n", crt_ps, threadid, NEXT);
		}
	}while(CURRENT_PASS < pass);
	exit();
}*/

void frisbee1(void* info){
	int crt_ps;
	uint pass = *(uint*)(info);
	uint thread_number = *(uint*)(info+4);
	uint threadid = *(uint*)(info+8);
	spinlock_t *spin_lock = *(spinlock_t**)(info+12);
	do{
		if(threadid == NEXT){
			spinlock_acquire(spin_lock);
			crt_ps = CURRENT_PASS;
			CURRENT_PASS = CURRENT_PASS + 1;
			if(thread_number == threadid + 1) NEXT = 0;
			else NEXT = NEXT + 1;
			spinlock_release(spin_lock);
			if(threadid+1 == thread_number)
				printf(1, "Pass number no: %d, Thread %d is passing the token to thread %d\n", crt_ps, threadid, NEXT);
			else
				printf(1, "Pass number no: %d, Thread %d is passing the token to thread %d\n", crt_ps, threadid, NEXT);
		}
		/*else{
			spinlock_acquire(spin_lock);
			printf(1,"Thread %d is reading...\n", threadid);
			sleep(10);
			spinlock_release(spin_lock);			
		}*/
	}while(CURRENT_PASS < pass);
	exit();
}

void frisbee2(void* info){
	int crt_ps;
	uint pass = *(uint*)(info);
	uint thread_number = *(uint*)(info+4);
	uint threadid = *(uint*)(info+8);
	qlock_t *q_lock = *(qlock_t**)(info+12);
	do{
		if(threadid == NEXT){
			qlock_acquire(q_lock, threadid);
			crt_ps = CURRENT_PASS;
			CURRENT_PASS = CURRENT_PASS + 1;
			if(thread_number == threadid + 1) NEXT = 0;
			else NEXT = NEXT + 1;
			qlock_release(q_lock, threadid);
			if(threadid+1 == thread_number)
				printf(1, "Pass number no: %d, Thread %d is passing the token to thread %d\n", crt_ps, threadid, NEXT);
			else
				printf(1, "Pass number no: %d, Thread %d is passing the token to thread %d\n", crt_ps, threadid, NEXT);
		}
	}while(CURRENT_PASS < pass);
	exit();
}


void frisbee3(void* info){
	int crt_ps;
	uint pass = *(uint*)(info);
	uint thread_number = *(uint*)(info+4);
	uint threadid = *(uint*)(info+8);
	seqlock_t *seq_lock = *(seqlock_t **)(info+12);
	do{
		if(threadid == NEXT){
			// play as a writer
			seqlock_writer_aquire(seq_lock);
			crt_ps = CURRENT_PASS;	
			CURRENT_PASS = CURRENT_PASS + 1;
			if(thread_number == threadid + 1) NEXT = 0;
			else NEXT = NEXT + 1;
			seqlock_writer_release(seq_lock);
			if(threadid+1 == thread_number)
				printf(1, "Pass number no: %d, Thread %d is passing the token to thread %d\n", crt_ps, threadid, NEXT);
			else
				printf(1, "Pass number no: %d, Thread %d is passing the token to thread %d\n", crt_ps, threadid, NEXT);
		
		}else{
			// play as a reader
			uint seq_num = 0;
			do{
				seq_num = seqlock_reader_aquire(seq_lock);
				// do sth
				//printf(1, "A reader is reading...\n");
			}while(seqlock_reader_retry(seq_lock, seq_num));
		}
	}while(CURRENT_PASS < pass);
	exit();
}


/*
** Usage: frisbee [thread number] [pass number] [lock type]
**     [lock type]: spinlock, queuelock
*/
int
main(int argc, char *argv[])
{
	int thread_number = atoi(argv[1]);
	int pass_time = atoi(argv[2]);
	int i;
	if(!strcmp(argv[3], "spinlock")){
		// test with spin lock
		spinlock_t spin_lock;
		spinlock_init(&spin_lock);
		for(i = 0; i < thread_number; i++){
			void* info = (uint*)malloc(40);
			*((uint*)(info)) = (uint)pass_time;
			*((uint*)(info+4)) = thread_number;
			*((uint*)(info+8)) = (uint)i;
			*((spinlock_t **)(info+12)) = (&spin_lock);
			thread_create(frisbee1, info);
		}
	}else if(!strcmp(argv[3], "queuelock")){
		//test with queuelock
		qlock_t q_lock;
		qlock_init(&q_lock, thread_number);
		for(i = 0; i < thread_number; i++){
			void* info = (uint*)malloc(40);
			*((uint*)(info)) = (uint)pass_time;
			*((uint*)(info+4)) = thread_number;
			*((uint*)(info+8)) = (uint)i;
			*((qlock_t **)(info+12)) = (&q_lock);
			thread_create(frisbee2, info);
		}
	}else if(!strcmp(argv[3], "seqlock")){
		//test with seqlock
		seqlock_t seq_lock;
		seqlock_init(&seq_lock);
		for(i = 0; i<thread_number; i++){
			void* info = (uint*)malloc(40);
			*((uint*)(info)) = (uint)pass_time;
			*((uint*)(info+4)) = thread_number;
			*((uint*)(info+8)) = (uint)i;
			*((seqlock_t **)(info+12)) = (&seq_lock);
			thread_create(frisbee3, info);
		}
	}else printf(1, "unknown lock type!");
	while(1) ;
	exit();
}