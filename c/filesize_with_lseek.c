/* filesize_with_lseek.c
 * Determine the size of a file with a single lseek64() call.
 * I know that I should use stat() for this task.
 */
#define _LARGEFILE64_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, const char **argv)
{
    int fd;
    long filesize;
    if(argc < 2) {
        fprintf(stderr, "No file given!\n");
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror("File open error");
        return 2;
    }
    filesize = lseek64(fd, 0, SEEK_END);
    printf("%liB\n", filesize);
    return 0;
}
