# include "kernel/types.h"
# include "user.h"
# include "kernel/param.h"

# define BUFSIZ 128

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
    printf("Allocate the memory space successfully.\n");
    read(fd, buf, BUFSIZ);
    split(buf, argAdd, &n);
    exit(0);
}

void split(char *args, char **argv, int *n)
{
    /* Preset the data */
    char *sta, *end, *idx;
    int i, len;
    *n = 0;
    len = strlen(args) - 1;
    sta = args;
    /* Skip the start blank space */
    for (sta = args; sta < args + len && *sta == ' ' && *sta != '\0'; sta++);
    printf("Skipped the openning blank space.\n");
    if (sta >= args + len)
    {
        printf("Start pointer find too many blank inputs or no input.\n");
        argv = 0;
    }
    /* Load in the arguments */
    else
    {
        for (end = sta; end < args + len; )
        {
            /* Read the argument's content util the first blank space */
            printf("1: end - sat = %d\n", end - sta);
            for (; *end != ' ' && *end != '\n'; end++);
            end--;
            printf("*end = %c\n", *end);
            printf("2: end - sat = %d\n", end - sta);
            printf("End pointer find the end of an argument.\n");
            /* Allocate space */
            printf("3: end - sat = %d\n", end - sta);
            printf("*n = %d\n", *n);
            argv[*n] = (char *)malloc(sizeof(char) * (end - sta + 2));
            printf("Allocate the memory space successfully.\n");
            /* Record the argument read in */
            printf("Record the argument: ");
            for (idx = sta, i = 0; idx <= end; idx++, i++)
            {
                argv[*n][i] = *idx;
                printf("%c", *idx);
            }
            argv[*n][i] = '\0';
            (*n)++;
            printf("!\n");
            /* Skip the blank space and reset the pointer */
            end++;
            for (; *end == ' ' && *end != '\n'; end++);
            if (end >= args + len)
            {
                printf("End pointer has scanned all the string.\n");
                break;
            }
            sta = end;
        }
    }
}
