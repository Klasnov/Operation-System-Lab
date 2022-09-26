#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user.h"

char *fmtName(char *path);
void find(char *path, char *name);

int main(int argc, char *argv[])
{
    // Verify the number of the arguments
    if (argc != 3)
    {
        printf("Find needs two arguments!\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}

void find(char *path, char *name)
{
    char buf[512], nm[512], *p;
    char *prt, *rct;
    int fd;
    struct dirent de;
    struct stat st;
    // Open the file
    prt = "..            ";
    rct = ".             ";
    memmove(nm, name, strlen(name));
    memset(nm + strlen(name), ' ', DIRSIZ - strlen(name));
    if ((fd = open(path, 0)) < 0)
    {
        printf("Failed to open %s!\n", path);
        return;
    }
    // Get the information of the file
    if (fstat(fd, &st) < 0)
    {
        printf("Failed to get the information of %s!\n", path);
        close(fd);
        return;
    }
    // Return if it's not a directory
    if (st.type != T_DIR)
    {
        fprintf(2, "There isn't a directory named %s!\n", path);
        return;
    }
    // Check the files in the directory
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf))
    {
        printf("The path is too long to read in!\n");
        close(fd);
        return;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    // Search the content of the directory
    int flag = 0;
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if (de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0)
        {
            printf("Failed to get the information of %s!\n", buf);
            continue;
        }
        // Check the type of the content
        char *fmtNam = fmtName(buf);
        switch (st.type)
        {
        case T_FILE:
            if (!strcmp(fmtNam, nm))
            {
                flag = 1;
                printf("%s\n", buf);
            }
            break;
        case T_DIR:
            if (strcmp(fmtNam, prt) && strcmp(fmtNam, rct))
            {
                find(buf, name);
            }
            break;
        }
    }
    if (!flag)
    {
        printf("Did not find %s.\n", name);
    }
    close(fd);
}

char *fmtName(char *path)
{
    static char buf[DIRSIZ + 1];
    char *p;
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;
    if (strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
    return buf;
}
