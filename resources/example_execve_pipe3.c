 #include <stdio.h>
  #include <memory.h>
  #include <unistd.h>
 #include <string.h>
 #include <stdlib.h>
  int main( int argc, char ** argv, char **env)
  {
   /* create the pipe */
   int pfd[2];
   if (pipe(pfd) == -1)
     {
       printf("pipe failed\n");
       return 1;
     }
	char  **a;
	a = (char **)malloc(sizeof(char *) * 3);
	a[0] = strdup("echo -n\0");
	a[1] = strdup("salut\0");
	a[2] = NULL;
   /* create the child */
   int pid;
   if ((pid = fork()) < 0)
     {
       printf("fork failed\n");
       return 2;
     }
 
   if (pid == 0)
     {
       /* child */
       close(pfd[1]); /* close the unused write side */
       dup2(pfd[0], 0); /* connect the read side with stdin */
       close(pfd[0]); /* close the read side */
       /* execute the process (wc command) */
       //execve("/usr/bin/pbcopy", NULL, NULL);
       execve("/bin/cat", NULL, NULL);
       printf("wc failed"); /* if execlp returns, it's an error */
       return 3;
     }
   else
     {
       /* parent */
       close(pfd[0]); /* close the unused read side */
       dup2(pfd[1], 1); /* connect the write side with stdout */
       close(pfd[1]); /* close the write side */
       /* execute the process (ls command) */
       execve("/bin/echo", a, NULL);
       printf("ls failed"); /* if execlp returns, it's an error */
       return 4;
     }
   return 0;
  }