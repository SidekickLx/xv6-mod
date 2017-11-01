#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
  int counter1 = 0;
  int counter2 = 0;
  counter1 = info(2);
  counter2 = info(2);
  printf(1, "counter1 = %d\t counter2 = %d\n", counter1, counter2);

  exit();
}