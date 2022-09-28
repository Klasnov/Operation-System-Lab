# include "kernel/types.h"
# include "user.h"

# define N 1

int main(int argc,char* argv[]) {
    if (argc != 1) {
        // Check the number of the parameters
        printf("Pingpong needs no argument!\n");
        exit(-1);
    }
    int p1[2], p2[2];
    int rtn, pid;
    char *i = "ping", *o = "pong", *rd = i;
    pipe(p1);
    pipe(p2);
    if ((rtn = fork()) < 0) {
        // Check whether the child process being created
        printf("Create the new process failed!\n");
    }
    if (rtn == 0) {
        pid = getpid();
        read(p1[0], rd, N);
        printf("%d: received ping\n", pid);
        close(p1[0]);
        write(p2[1], o, N);
        close(p2[1]);
    }
    else {
        pid = getpid();
        write(p1[1], i, N);
        close(p1[1]);
        read(p2[0], rd, N);
        printf("%d: received pong\n", pid);
        close(p2[0]);
    }
    exit(0);
}
