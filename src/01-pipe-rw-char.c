#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>

int 
main (int argc, char* argv[])
{
    int pipe_fd[2];
    pid_t pid;
    char ch;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>. \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipe_fd[1]);
        sleep(1);
        while (read(pipe_fd[0], &ch, 1) > 0)        /* pipe_fd[0] is read end */
            write(STDOUT_FILENO, &ch, 1);

        write(STDOUT_FILENO, "\n", 1);
        close(pipe_fd[0]);
        _exit(EXIT_SUCCESS);

    } else {
       close(pipe_fd[0]); 
       write(pipe_fd[1], argv[1], strlen(argv[1]));  
       close(pipe_fd[1]);
       wait(NULL);
       exit(EXIT_SUCCESS);
    }
}
