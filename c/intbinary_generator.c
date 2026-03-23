/* intbinary_generator.c
 * Generate a binary file filled with integers received from stdin.
 * */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char **argv)
{
    int fd, number;
    if(argc < 2) {
        fprintf(stderr, "Pass a filename to store integers\n");
        return 1;
    }
    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0666);
    if(fd == -1) {
        perror(argv[1]);
        return 2;
    }
    while(scanf("%d", &number) != EOF) {
        int cnt;
        cnt = write(fd, &number, sizeof(number));
        if(cnt == -1)
            perror(argv[1]);
    }
    fsync(fd);
    close(fd);
    return 0;
}
