#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define CHILD_NUM    4
#define GCHILD_CHILD 2
#define TOTALPROC  (CHILD_NUM + (CHILD_NUM*GCHILD_CHILD))

void childDo(int pidP, int childNum)
{
   printf("My parent has PID = %d;I am the %d child; my PID is %d \n", pidP, childNum, getpid());
   pidP = getpid();
   
   for(int i = 0; i < GCHILD_CHILD; i++)
   {
     if(fork() == 0)
     {
       printf("My parent has PID = %d; I am a grandchild; my PID is %d \n", pidP, getpid());
       break;
     }
   }
}

int main(void)
{
   int pidP, pidC, pidGC;
   int status;
   
   for(int i = 0; i < CHILD_NUM; i++)
   {
     if(fork() == 0)
     {
       childDo(getpid(), i);
       break;
     }
   }
   
   for(int i = 0; i < TOTALPROC; i++)
   {
        wait(&status);
   }
   return 0;
}
