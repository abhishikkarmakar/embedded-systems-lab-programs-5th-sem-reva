#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <string.h>
#include<pthread.h>
#include <unistd.h>

int main ()
{
int fd[2];
pid_t childpid;
char string[]= " REVA University \n";
char readbuffer[80];
pipe(fd);
if((childpid=fork())==-1)
{
perror("fork");
return 0;
}
if (childpid==0)
{
close(fd[0]);
write (fd[1], string, strlen(string));
return 0;
}
else
{close(fd[1]);
read (fd[0], readbuffer, sizeof(readbuffer));
printf(" Received string is %s", readbuffer); }
return(0);
}
