#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
  printf(1, "The number of the processes in the system is %d\n", info(1));
  printf(1, "The number of of the total number of system calls that a process has done so far is %d\n", info(2));
  printf(1, "The number of memorypages the current process using is %d\n", info(3));
  exit();
}