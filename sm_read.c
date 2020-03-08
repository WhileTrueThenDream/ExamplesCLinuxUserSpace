/*
   It reads from a previously created memory object "/myMemoryObj"
   to be compiled with "-lrt"
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
 
#define SMOBJ_NAME  "/myMemoryObj"

int main(void)
{
   int fd;
   char *ptr;
   struct stat shmobj_st;
   
   fd = shm_open (SMOBJ_NAME,  O_RDONLY  , 00400); /* open s.m object*/
   if(fd == -1)
   {
       printf("Error file descriptor %s\n", strerror(errno));
	   exit(1);
   }
   
   if(fstat(fd, &shmobj_st) == -1)
   {
       printf(" error fstat \n");
	   exit(1);
   }
   ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Map failed in read process: %s\n", strerror(errno));
      exit(1);
   }
   
   printf("%s \n", ptr);
   close(fd);
   
   return 0;
}
