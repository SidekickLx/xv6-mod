#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

uint shared=0;


void t_test(void* p){
	printf(1, "\thello\n");
	exit();
}

int
main(int argc, char *argv[])
{
	int i =1;
	thread_create(&t_test, &i);
	exit();
}