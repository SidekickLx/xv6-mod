#include "types.h"
#include "stat.h"
#include "user.h"

#define RAND_MAX 0x7FFFFFFF

static long do_rand(unsigned long *value)
{
  long quotient, remainder, t;

  quotient = *value / 127773L;
  remainder = *value % 127773L;
  t = 16807L * remainder - 2836L * quotient;

  if (t <= 0)
     t += 0x7FFFFFFFL;
  return ((*value = t) % ((unsigned long)RAND_MAX + 1));
}
static unsigned long next = 1;
uint random(int max)
{
  return (uint)(do_rand(&next) % max);
}

void srandom(uint seed)
{
  next = seed;
}

//for test 
// int main(void){
//   int ticket_sum = 20;
//   int winner_ticket = 0;
//   srandom(uptime());
//   winner_ticket = random(ticket_sum);
//   printf(1,"winner_ticket = %d\n", winner_ticket);
//   exit();
// }