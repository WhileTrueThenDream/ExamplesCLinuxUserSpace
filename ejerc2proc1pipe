/****************************************************************/
/* Programar "ls -l | wc > file1.txt"                            */
/* El archivo file1.txt existe                                  */
/* TODO: manejo de errores                                      */
/****************************************************************/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>


#define READ_END    0    /* index pipe extremo escritura */
#define WRITE_END   1    /* index pipe extremo lectura */

#define FILE_NAME  "file.txt"   /* nombre del archivo donde escribir */

int main(int argc, char* argv[])   
{
    int fd1[2],fd2;
    int status, pid;
    
    pipe(fd1);                  /* comunica ls y wc */
    
    pid = fork();     

    if(pid == 0)                /* hijo 1, ejecuta "ls -la" */
    {              
        close(fd1[READ_END]);   /* cerrar extremo no necesario */
        
        dup2(fd1[WRITE_END], STDOUT_FILENO); 
        close(fd1[WRITE_END]);
        
        execlp("/bin/ls", "ls", "-la", NULL);
    }
    else                          /* padre */
    { 
        close(fd1[WRITE_END]);    /* extremo no necesario ya */
        
        pid = fork();
		
       if(pid == 0)               /* hijo 2, ejecuta "wc" */
       {     
          fd2 = open(FILE_NAME, O_WRONLY);
          dup2(fd1[READ_END], STDIN_FILENO);
          close(fd1[READ_END]);
		   		   
          dup2(fd2, STDOUT_FILENO);		   
            
          execlp("/usr/bin/wc","wc",NULL);
       }
       else /* padre */
       {
           close(fd1[READ_END]);      /* cerrar extremo no necesario */    
       }                
     }
    
   /* wait para cada hijo */
    wait(&status);   
    wait(&status);    
    
    return 0;    
}
    
