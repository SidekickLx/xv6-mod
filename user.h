#ifndef _USER_H_
#define _USER_H_
struct stat;
struct rtcdate;

typedef struct __spinlock_t{
	uint locked;
}spinlock_t;

typedef struct __qlock_t{
	uint qsize;
	uint tail;
	int *flag;
}qlock_t;

typedef struct{
	uint seq;
	spinlock_t spinlock;
} seqlock_t;


// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int info(int);
int atckt(int);
int clone(void*, int);

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
uint random(int);
void srandom(uint);

//thread.c
int spinlock_init(spinlock_t* lock);
void spinlock_acquire(spinlock_t *lock);
void spinlock_release(spinlock_t *lock);
int qlock_init(qlock_t *lock, uint size);
void qlock_acquire(qlock_t *lock, int slot);
void qlock_release(qlock_t *lock, int slot);
int seqlock_init(seqlock_t *lock);
void seqlock_writer_aquire(seqlock_t *lock);
void seqlock_writer_release(seqlock_t *lock);
int seqlock_reader_aquire(seqlock_t *lock);
int seqlock_reader_retry(seqlock_t *lock, int startseq);
int thread_create(void (*start_routine)(void*), void *arg);

#endif // _USER_H_