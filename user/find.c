# include "kernel/types.h"
# include "kernel/stat.h"
# include "kernel/fs.h"
# include "user.h"

void find(char *path, char *name);

int main(int argc, char *argv[]) {
    // Verify the number of the arguments
    if (argc != 3) {
        printf("Find needs two arguments!\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}

void find(char *path, char *name) {
    int fd;
    struct stat st;
    // Open the file
    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "The file doesn't exist!\n");
        return;
    }
    // Get the information of the file
    if (fstat(fd, &st) < 0) {
        
    }
}
