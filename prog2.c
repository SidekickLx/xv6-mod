#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[])
{
    applyticket(50);
    int i, k;
    const int loop = 43000;
    for (i = 0; i < loop; i++)
    {
        // write your own function here
        asm("nop"); //in order to prevent the compiler from optimizing the for loop for(k=0;k<loop;k++)
        for (k = 0; k < loop; k++)
        {
            asm("nop");
        }
        printf(1, "program 2 finished loop %d\n", i);
    }
    exit();
}