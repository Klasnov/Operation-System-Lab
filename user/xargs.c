#include "kernel/types.h"
#include "user.h"
#include "kernel/param.h"

#define BUFSIZ 512

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Xargs needs at least two arguments!\n");
        exit(0);
    }
    int fd;
    fd = dup(0);
    char buf[BUFSIZ];
    read(fd, buf, BUFSIZ);
    printf("buf = %s\n", buf);
    exit(0);
}

char **split(char *args, int *n)
{
    char *sta, *end, *idx, **argv;
    *n = 0;
    sta = args;
    // Skip the start space
    for (sta = args; sta < args + BUFSIZ && *sta == ' '; sta++)
        ;
    // Load in the arguments
    if (sta >= args + BUFSIZ)
    {
        return 0;
    }
    else
    {
        for (end = sta; end < args + BUFSIZ;)
        {
            // Read the argument's content
            for (; *end != ' '; end++)
                ;
            end--;
            argv[*n] = (char *)malloc(sizeof(char) * (end - sta));
        }
    }
}
