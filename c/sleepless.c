/* sleepless.c
 * The program awaits input from the user.
 * If the user doesn't write anything for 5 seconds,
 * the program asks the user if (s)he fell asleep.
 * Ends if the user sends SIGINT (^C) twice
 * with a gap shorter than 5 seconds.
 */
#include <sys/select.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

/* Consts */
#define WAITTIME 5
const char startmsg[] = "You may write some text here.\n";
const char dontsleepmsg[] = "\nHey, are you sleeping there?\n";
const char reportmsg[] = "\nThe amount of strings: %d, and the chars: %d\n";

/* External */
extern int errno;

/* Signal handler */
volatile static sig_atomic_t timestamp = 0;
void sigint_handler(int s)
{
    int save_errno = errno;
    signal(SIGINT, sigint_handler);
    if(time(NULL) - timestamp < 5)
        exit(0);
    timestamp = time(NULL);
    errno = save_errno;
}

/* The rest */
void stdin_event(int *chars, int *strings)
{
    int cnt, i;
    char buf[4096];
    cnt = read(0, buf, 4096); /* read stdin, 4096 chars max */
    *chars += cnt;
    for(i = 0; i < cnt; i++) {
        if(buf[i] == '\n')
            (*strings)++;
    }
}

int main()
{
    struct timeval t;
    fd_set readfd;
    int event, chars = 0, strings = 0;
    signal(SIGINT, sigint_handler);
    FD_SET(0, &readfd);
    write(1, startmsg, sizeof(startmsg)-1);
    for(;;) {
        t.tv_sec = WAITTIME;
        t.tv_usec = 0;
        event = select(1, &readfd, NULL, NULL, &t);
        if(event == 0) {                           /* timeout */
            write(1, dontsleepmsg, sizeof(dontsleepmsg)-1);
        } else if(event == -1 && errno == EINTR) { /* SIGINT */
            printf(reportmsg, strings, chars);
        } else {                                   /* assume it's stdin */
            stdin_event(&chars, &strings);
        }
        if(!FD_ISSET(0, &readfd))
            FD_SET(0, &readfd);
    }
    return 0;
}
