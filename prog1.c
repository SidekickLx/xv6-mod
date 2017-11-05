#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[])
{
    applyticket(100);
    int i, k;
    const int loop = 430000;
    for (i = 0; i < loop; i++)
    {
        // write your own function here
        asm("nop"); //in order to prevent the compiler from optimizing the for loop for(k=0;k<loop;k++)
        for (k = 0; k < loop; k++)
        {
            asm("nop");
        }
        printf(1, "program 1 finished loop %d\n", i);
    }
    exit();
}