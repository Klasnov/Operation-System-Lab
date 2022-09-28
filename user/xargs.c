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
    /* Verify the account of the arguments */
    if (argc < 2)
    {
        printf("Xargs needs at least two arguments!\n");
        exit(0);
    }
    /* Data preset */
    int n, i, id, stat;
    char buf[BUFSIZ];
    char **argAdd, **exAg;
    argAdd = (char **)malloc(sizeof(char *) * (MAXARG - argc));
    /* Circle of reading the input and execute command */
    while(1)
    {
        /* Parse the string input in */
        if (!strcmp(gets(buf, BUFSIZ), ""))
        {
            break;
        }
        split(buf, argAdd, &n);
        /* Create the arguments pointer of exec() */
        exAg = (char **)malloc(sizeof(char *) * (n + argc));
        for (i = 0; i < argc - 1; i++)
        {
            exAg[i] = argv[i + 1];
        }
        for (int j = 0; j < n; j++)
        {
            exAg[i++] = argAdd[j];
        }
        exAg[i] = 0;
        /* Create the parent and child pocess to execute the command */
        if ((id = fork()) < 0)
        {
            printf("Failed to create the child process!\n");
        }
        /* Child process execute the command */
        if (id == 0)
        {
            exec(argv[1], exAg);
            exit(0);
        }
        /* Parent process wait until child process exited */
        else
        {
            wait(&stat);
        }
    }
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
    if (sta >= args + len)
    {
        argv = 0;
    }
    /* Load in the arguments */
    else
    {
        for (end = sta; end < args + len; )
        {
            /* Read the argument's content util the first blank space */
            for (; *end != ' ' && *end != '\n'; end++);
            end--;
            /* Allocate space */
            argv[*n] = (char *)malloc(sizeof(char) * (end - sta + 2));
            /* Record the argument read in */
            for (idx = sta, i = 0; idx <= end; idx++, i++)
            {
                argv[*n][i] = *idx;
            }
            argv[*n][i] = '\0';
            (*n)++;
            /* Skip the blank space and reset the pointer */
            end++;
            for (; *end == ' ' && *end != '\n'; end++);
            if (end >= args + len)
            {
                break;
            }
            sta = end;
        }
    }
}
