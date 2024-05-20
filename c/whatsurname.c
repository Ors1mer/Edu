/*
 * The program asks the user's name, than awaits
 * for an answer for N seconds. If the user writes
 * his name, it greets him. Finishes otherwise.
 *
 * The program is done using the select system call.
 */
#include <sys/select.h>
#include <stdio.h>
#include <aio.h>

#define N 15
#define STDIN_DESCR 0
#define UNAME_MAX 128

int main()
{
    struct timeval t;
    fd_set readfd;
    char uname[UNAME_MAX];
    int ok;
    t.tv_sec = N;
    t.tv_usec = 0;
    FD_SET(STDIN_DESCR, &readfd);

    printf("What's your name?\n");
    ok = select(STDIN_DESCR+1, &readfd, NULL, NULL, &t);
    if(ok) {
        scanf("%128s", uname);
        printf("Nice to meet you, dear %s!\n", uname);
    } else {
        printf("Sorry, I'm terribly busy.\n");
    }

    return 0;
}
