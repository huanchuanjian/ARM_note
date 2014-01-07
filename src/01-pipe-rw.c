#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
    int pipe_fd[2];
    pid_t pid;
    char buffer[BUF_SIZE];
    int bytes_read;

    memset(buffer, 0, BUF_SIZE);    /* fill BUF_SIZE bytes with 0 */
    
    /* create pipe */
    if (pipe(pipe_fd) < 0) {
        fprintf(stderr, "Create pipe error.\n");
        exit(EXIT_FAILURE);
    }

    /* create child process */
    if ((pid = fork()) < 0) {
        fprintf(stderr, "Create process error.\n");
        exit(EXIT_FAILURE);

    } else if (pid == 0) {          /* read from parent */
        close(pipe_fd[1]);
        sleep(2);                   /* wait for writing */

        if ((bytes_read = read(pipe_fd[0], buffer, BUF_SIZE)) > 0) {
            fprintf(stdout, "Read from parent: %s\n", buffer);
            close(pipe_fd[0]);
        }
        
    } else {                        /* write to child */
        close(pipe_fd[0]);
        if (write(pipe_fd[1], "hello", 5) != -1) {
            printf("Write OK.\n");
        }

        if (write(pipe_fd[1], " pipe", 5) != -1) {
            printf("Write OK.\n");
        }
        
        sleep(3);
        wait(NULL);
    }
    
    exit(EXIT_SUCCESS);
}
