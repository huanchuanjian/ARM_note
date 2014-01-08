#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

void foo()
{
    int i, j;
    int y = 0;
    for (i = 0; i < 1000; i++) {
        for (j = 0; j < 1000; j++) {
            /* do sth */
            y++; 
        }
    }
}

int main(int argc, char* argv[])
{
    float timeuse;
    struct timeval tv_start;
    struct timeval tv_end;

    gettimeofday(&tv_start, NULL);
    foo();
    gettimeofday(&tv_end, NULL);

    timeuse = 1000000*(tv_end.tv_sec - tv_start.tv_sec) + 
              tv_end.tv_usec - tv_start.tv_usec;

    printf("Time of foo: %f\n", timeuse / 1000000);

    exit(EXIT_SUCCESS);
}
