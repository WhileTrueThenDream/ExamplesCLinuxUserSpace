/*
 This program : 
 - Loads a file into virtual memory with mmap
 - Looks occurrences of one determined character in file
 - Replaces all that occurrences for another determined character in file. 
 
 Input arguments
 -  argv[1] --> file name an path
 - *argv[2] --> character to be looked for 
 - *argv[3] --> character which replaces the found ones
 
 Example: memMMapExm a A /* 'a' character will be replaced in file with 'A' character 
 */

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	char *addr, *file_name;
	int fd;
	struct stat file_st;
	char seekchar, newchar;
	
	if(argc == 4)
	{
		file_name = argv[1];
		seekchar = *argv[2];
		newchar = *argv[3];
	}
	else
	{
		printf("Error argument number \n");
		exit(-1);
	}
	
	if( -1 == (fd = open(file_name, O_RDWR)))
	{
		perror("Error opened file \n");
		exit(-1);
	}
	
	fstat(fd, &file_st);
	
	addr = mmap(NULL,file_st.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == MAP_FAILED)
	{
		perror("Error  mapping \n");
		exit(-1);
	}
	
    printf("file contents before:\n%s \n", addr);
	
	for(size_t i = 0; i < file_st.st_size; i++)
	{
		if (addr[i] == seekchar) 
		   (addr[i] = newchar) ;
	}
	   
	printf("file contents after:\n%s \n", addr);
	   
	return 0;
}
