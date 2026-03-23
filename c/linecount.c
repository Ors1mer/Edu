/* linecount.c
 * Count the number of lines in a file.
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFSIZE 4096
int main(int argc, const char **argv)
{
    int fd, linecnt = 0;
    char buffer[BUFFSIZE];
    if(argc < 2) {
        fprintf(stderr, "No file given");
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror(argv[1]);
        return 2;
    }
    for(;;) {
        int cnt, i;
        cnt = read(fd, buffer, BUFFSIZE);
        if(cnt == -1) {
            perror(argv[1]);
            break;
        } else if(cnt == 0) {
            break;
        }
        for(i = 0; i < cnt; i++)
            if(buffer[i] == '\n')
                linecnt++;
    }
    close(fd);
    printf("%d\n", linecnt);
    return 0;
}
