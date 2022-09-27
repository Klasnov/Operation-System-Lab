# include "kernel/types.h"
# include "user.h"
# include "kernel/param.h"

# define BUFSIZ 256

/*
Split the input string into different arguments.
@ para args: The input string.
@ para n   : A pointer used to return the number of the arguments.
@ para argc: The number of the arguments still can be added.
@ return:  : The pointer containing all the arguments.
*/
void split(char *args, char **argv, int *n);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Xargs needs at least two arguments!\n");
        exit(0);
    }
    int fd, n;
    char buf[BUFSIZ];
    char **argAdd;
    fd = dup(0);
    argAdd = (char **)malloc(sizeof(char *) * MAXARG - argc);
    read(fd, buf, BUFSIZ);
    split(buf, argAdd, &n);
    printf("Run successfully!\n");
    exit(0);
}

void split(char *args, char **argv, int *n)
{
    // Preset the data
    char *sta, *end, *idx;
    int i, len;
    *n = 0;
    len = strlen(args) - 1;
    sta = args;
    // Skip the start blank space
    for (sta = args; sta < args + len && *sta == ' '; sta++);
    if (sta >= args + len) argv = 0;
    // Load in the arguments
    else
    {
        for (end = sta; end < args + len; )
        {
            // Read the argument's content util the first blank space
            for (; *end != ' ' && *end != '\0' && end < args + len; end++);
            if (end >= args + len)
            {
                if (*n != 0) break;
                else
                {
                    argv = 0;
                    break;
                }
            }
            end--;
            // Allocate space
            argv[*n] = (char *)malloc(sizeof(char) * (end - sta + 2));
            // Record the argument read in
            for (idx = sta, i = 0; idx <= end; idx++, i++) argv[*n][i] = *idx;
            argv[*n][i] = '\0';
            n++;
            // Skip the blank space and reset the pointer
            end++;
            for (; *end == ' ' && *end != '\0'; end++);
            if (end >= args + len) break;
            sta = end;
        }
    }
}
