#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define READ_END    0    /* index pipe extremo escritura */
#define WRITE_END   1    /* index pipe extremo lectura */

int main(int argc, char* argv[])   
{
    int fd1[2],fd2[2];
    int status, pid;
	
    pipe(fd1);                 /* comunica ls y grep */
	
    pid = fork();     

    if(pid == 0)              /* hijo 1*/
    {      		
        close(fd1[READ_END]);   /* cerrar extremo no necesario */
		
        dup2(fd1[WRITE_END], STDOUT_FILENO); 
	close(fd1[WRITE_END]);
		
        execlp("/bin/ls", "ls", "-l", NULL);
    }
    else                          /* padre */
    { 
	close(fd1[WRITE_END]);    /* extremo no necesario ya */
		
	pipe(fd2);		  /* comunica grep y wc */
        pid = fork();
        
       if(pid == 0)               /* hijo 2 */
       {
	  close(fd2[READ_END]);   /* cerrar extremo no necesario */
									
          dup2(fd1[READ_END], STDIN_FILENO);
	  close(fd1[READ_END]);
			
	  dup2(fd2[WRITE_END], STDOUT_FILENO);			
	  close(fd2[WRITE_END]);
			
          execlp("/bin/grep","grep", "u",NULL);
	}
	else /* padre */
	{
           close(fd1[READ_END]);      /* cerrar extremo no necesario */
           close(fd2[WRITE_END]);     /* cerrar extremo no necesario */
			
     	   pid = fork();
		
	   if(pid == 0) /* hijo 3*/
          {
	    dup2(fd2[READ_END], STDIN_FILENO);
	    close(fd2[READ_END]);
				
	    execlp("/usr/bin/wc","wc", "-l",NULL);
	  }
        }		        
      }
    
    close(fd2[READ_END]);  /* cerrar extremo que queda abierto en el padre  */
	
   /* wait para cada hijo */
    wait(&status);   
    wait(&status);	
    wait(&status);
	
    return 0;
  	
}
	



