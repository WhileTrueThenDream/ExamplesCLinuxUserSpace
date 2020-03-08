/*
  - Parent creates a children
  - Children writes its PID on shared memory
  - Children terminates, parent waits for it. 
  
  This process is repeated 5 times
  
  At the end parent outputs in terminal shared memory contents. 
  
  To be compiled with -lrt flag

*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <stdlib.h>


#define CHILD_NUM    4

int main(void)
{
    int fd, status, pid;
    int *ptr, *ptrcp;
    
    fd = shm_open("/myMemoryObj", O_CREAT | O_RDWR  , 0600); /* create s.m object*/   
    ftruncate(fd, CHILD_NUM*sizeof(getpid()));                                 /* resize memory object */
    ptr = mmap(NULL, CHILD_NUM*sizeof(getpid()), PROT_WRITE, MAP_SHARED, fd, 0);
    ptrcp = ptr;
	
	for(int i = 0; i < CHILD_NUM; i++)
    {
	  switch(fork())
	  {
		  case 0:
		   *(ptr + i) = getpid();					
			exit(0);
          break;
		  case -1 :
		   printf("Child not created \n");
		  break;
		  default:
            wait(&status); /* wait for child before creating another one */
		  break;
	  }
   
   }
     
   for(int i = 0; i < CHILD_NUM;i++)
   {
      printf("PID child %d: %d \n", i, *ptrcp);
      ptrcp++;
   }
   
   return 0;
}
