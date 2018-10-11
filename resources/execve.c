#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <sys/wait.h>

/* since pipes are unidirectional, we need two pipes.
   one for data to flow from parent's stdout to child's
   stdin and the other for child's stdout to flow to
   parent's stdin */
 
#define NUM_PIPES          2
 
#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1
 
int pipes[NUM_PIPES][2];
 
/* always in a pipe[], pipe[0] is for read and 
   pipe[1] is for write */
#define READ_FD  0
#define WRITE_FD 1
 
#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD]   )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )
 
#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD]  )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD]  )

int main(int argc, char **av, char **env)
{
    int     outfd[2];
    int     infd[2];
    pid_t   pid;
    pid_t   fpid;
     
    // pipes for parent to write and read
    pipe(pipes[PARENT_READ_PIPE]);
    pipe(pipes[PARENT_WRITE_PIPE]);
    
    if ((fpid = fork()) == -1)
        return (0);
    else if (fpid == 0) {
        //char *argv[]={ "/bin/bash", 0};
        //char *argv[]={ "/usr/bin/man", "echo", 0};
        char *argv[]={ "/bin/cat", "/dev/random", 0};
 
        // dup2(CHILD_READ_FD, STDIN_FILENO);
        // dup2(CHILD_WRITE_FD, STDOUT_FILENO);
 
        /* Close fds not required by child. Also, we don't
           want the exec'ed program to know these existed */
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);
          
       
        execve(argv[0], argv, env);
        printf("An error occured\n");

    } else {

        char    buffer[4096];
        int     count;
        int     j;
        int     status;
 
        // /* close fds not required by parent */       
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
 
        // Write to child’s stdin
        write(PARENT_WRITE_FD, "", 0);
  
        // Read from child’s stdout
        // while ((count = read(PARENT_READ_FD, buffer, sizeof(buffer) - 1)) > 0)
        // {
        //     buffer[count] = '\0';
        //     printf("%s", buffer);
        //     bzero(buffer, 4096);
        // }
        pid = wait(&status);
        if (WIFEXITED(status))
            printf("Parent: Child exited with status: %d\n", WEXITSTATUS(status));
    }
    return (0);
}