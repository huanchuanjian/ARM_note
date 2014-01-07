#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int pipe_fd[2];
    
    if (pipe(pipe_fd) < 0) {
        fprintf(stderr, "pipe create error\n");
        exit(EXIT_FAILURE);
    } else {
        fprintf(stdout, "pipe create successfully.\n");
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    exit(EXIT_SUCCESS);    
}
