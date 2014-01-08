#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    time_t t;
    struct tm* gm_tm;

    t = time(NULL);
    gm_tm = gmtime(&t);

    printf("%s", asctime(gm_tm));
    printf("%s", ctime(&t));
    
    exit(EXIT_SUCCESS);
}
