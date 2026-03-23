/* envr.c
 * The program gets the name of the user
 * through $HOME (assuming the variable is present
 * and looks like "/home/username"), then greets the user.
 * If $HOME isn't set or incorrect, greets anonymous
 */
#include <stdio.h>
#include <stdlib.h>

#define ENV_HOME "HOME"
#define ANONYM_GREET "Hello, anonymous!\n"

extern char **environ;

char *title(const char *str)
{
    enum { tsize = 128 };
    unsigned int i;
    char *title = malloc(tsize);

    *title = *str; /* copy the first symbol */
    if(*title >= 'a' && *title <= 'z') /* make uppercase if necessary */
        *title -= 32;

    for(i = 1; i < tsize && *(str+i); i++)
        *(title+i) = *(str+i);

    return title;
}

size_t string_len(const char *str)
{
    const char *p;
    for(p = str; *p; p++)
        {}
    return p - str;
}

int startswith(const char *str1, const char *str2)
{
    for(; *str2; str1++, str2++) {
        if(!str1 || *str1 != *str2)
            return 0;
    }
    return 1;
}

int main()
{
    const char *usrname;

    usrname = getenv(ENV_HOME);
    if(usrname && startswith(usrname, "/home/") && string_len(usrname) > 6) {
        usrname += 6; /* skips "/home/" */
        printf("Hello, %s!\n", title(usrname));
    } else {
        printf(ANONYM_GREET);
    }

    return 0;
}
