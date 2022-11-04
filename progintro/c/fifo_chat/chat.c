/* chat.c
 * Launch in two terminals like './chat f1 f2' and './chat f2 f1',
 * where f1 & f2 - named pipes.
 * Write text in any, press enter and see what happens.
 */
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

const char argerrmsg[] = "Not enough arguments (file1 & file2)\n";
const char userquitmsg[] = "The user left the chat.\n";

void redirect(int fromfd, int tofd, int fd1, int fd2)
{
    char buf[1024];
    int cnt, writecnt;
    cnt = read(fromfd, buf, sizeof(buf)-1);
    if(!cnt) { /* EOF */
        if(fromfd == fd1)
            write(0, userquitmsg, sizeof(userquitmsg)-1);
        close(fd1); close(fd2);
        exit(0);
    }
    writecnt = write(tofd, buf, cnt);
    if(writecnt != cnt) {
        close(fd1); close(fd2);
        exit(3);
    }
    cnt = read(fromfd, buf, sizeof(buf)-1);
    while(cnt > 0) {
        writecnt = write(tofd, buf, cnt);
        if(writecnt != cnt) {
            close(fd1); close(fd2);
            exit(3);
        }
        cnt = read(fd1, buf, sizeof(buf)-1);
    }
}

void main_cycle(int fd1, int fd2)
{
    fd_set readfd;
    for(;;) {
        FD_ZERO(&readfd);
        FD_SET(0, &readfd);
        FD_SET(fd1, &readfd);

        select(fd1+1, &readfd, NULL, NULL, NULL);

        if(FD_ISSET(fd1, &readfd)) {
            redirect(fd1, 1, fd1, fd2);
        } else if(FD_ISSET(0, &readfd)) {
            redirect(0, fd2, fd1, fd2);
        } else {
            close(fd1);
            close(fd2);
            exit(4);
        }
    }
}

int main(int argc, const char **argv)
{
    int fd1, fd2;
    if(argc < 3) {
        write(2, argerrmsg, sizeof(argerrmsg)-1);
        exit(1);
    }

    fd1 = open(argv[1], O_RDONLY | O_NONBLOCK);
    if(fd1 == -1) {
        perror("open file1");
        exit(2);
    }
    fd2 = open(argv[2], O_WRONLY);
    if(fd2 == -1) {
        close(fd1);
        perror("open file2");
        exit(2);
    }

    main_cycle(fd1, fd2);
    return 0;
}
