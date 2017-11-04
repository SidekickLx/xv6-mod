#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[])
{
    applyticket(250);
    int i, k;
    const int loop = 43000;
    for (i = 0; i < loop; i++)
    {
        asm("nop"); //in order to prevent the compiler from optimizing the for loop for(k=0;k<loop;k++)
        for (k = 0; k < loop; k++)
        {
            asm("nop");
        }
        printf(1, "program 3 finished loop %d\n", i);
    }
    exit();
}