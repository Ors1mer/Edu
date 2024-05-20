#include <stdio.h>
#include <time.h>

#define DAY_IN_SEC 24*3600

/*
 * The program stores the time of a past event in the time_t variable,
 * then writes to stdin amount of days passed since the event.
*/

int string_len(const char *str)
{
    const char *p;
    for(p = str; *p; p++)
        {}
    return p - str;
}

int main()
{
    char msg[64] = "Time since ~event~: %d days\n";
    time_t event = 1658473165; /* The Unix time of a past event here */
    time_t now, diff;
    int days_since;

    now = time(NULL);
    diff = now - event;

    days_since = 0;
    while(diff >= DAY_IN_SEC) {
        diff -= DAY_IN_SEC;
        days_since++;
    }
    if(days_since == 1) {
        /* Rewrite the word: "days" -> "day" */
        int msg_len = string_len(msg);
        msg[msg_len-2] = '\n';
        msg[msg_len-1] = '\0';
    }

    printf(msg, days_since);
    return 0;
}
