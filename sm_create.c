/*
   It creates a memory object "/myMemoryObj"
   Object can be found: /dev/shm
   to be compiled with "-lrt"
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>

#define SIZEOF_SMOBJ 200
#define SMOBJ_NAME  "/myMemoryObj"

int main(void)
{
   int fd;
   fd = shm_open (SMOBJ_NAME, O_CREAT | O_RDWR  , 00700); /* create s.m object*/
   if(fd == -1)
   {
       printf("Error file descriptor \n");
	   exit(-1);
   }
   if(-1 == ftruncate(fd, SIZEOF_SMOBJ))
   {
       printf("Error shared memory cannot be resized \n");
	   exit(-1);
   }
   
   close(fd);
   
   return 0;
}
