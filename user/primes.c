# include "kernel/types.h"
# include "user.h"
# define N 34

void sieve(int p[], int n);

int main(int argc, char *argv[]) {
    // Determine the number of the input
    if (argc != 1) {
        printf("Primes doesn't need any argument!\n");
        exit(-1);
    }
    // Initialize the data
    int num[N] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
    // Create the initial input
    int p[2];
    pipe(p);
    write(p[1], num, N * 4);
    close(p[1]);
    // Recursive solution
    sieve(p, N);
    // Exit the function securely
    exit(0);
}

void sieve(int p[], int n) {
    int rtn, prm, cldStt, ipt[n];
    // Failed to create the new process
    if ((rtn = fork()) < 0) {
        printf("Create the new process failed!\n");
    }
    // Child Process
    if (rtn == 0) {
        // Get data from the pipe and close it.
        read(p[0], ipt, n * 4);
        prm = ipt[0];
        printf("prime %d\n", prm);
        close(p[0]);
        // Recursive solution
        if (n != 1) {
            // Traverse the array and select elements
            int opt[n], cnt = 0;
            for (int i = 1; i < n; i++) {
                if (ipt[i] % prm != 0) {
                    opt[cnt++] = ipt[i];
                }
            }
            // Create a new pipe and transmit data
            int p[2];
            pipe(p);
            write(p[1], opt, cnt * 4);
            close(p[1]);
            // Recrusion
            sieve(p, cnt);
        }
        exit(0);
    }
    // Parent Process
    else {
        wait(&cldStt);
        exit(0);
    }
}
