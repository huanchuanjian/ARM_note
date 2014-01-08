#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    time_t t;
    struct tm* local;

    t = time(NULL);
    local = localtime(&t);
    printf("Local time, year is %d\n", local->tm_year + 1900);
    printf("Local hour: %d\n", local->tm_hour);

    local = gmtime(&t);
    printf("UTC time, year is %d\n", local->tm_year + 1900);
    printf("UTC hour: %d\n", local->tm_hour);

    exit(EXIT_SUCCESS);
}
