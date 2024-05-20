#include <stdio.h>

/* Calculating string's length without strlen */
/* Optimal: not too many operations, readable */
int string_len(const char *str)
{
    const char *p;
    for(p = str; *p; p++)
        {}
    return p - str;
}

/* This isn't recommended: side effect in while(), harder to understand */
int string_len_v2(const char *str)
{
    const char *p = str;
    while(*p++);
    return p - str - 1;
}

/* Copying a string without strcpy */
/* Optimal solution */
void string_copy(char *dest, const char *src)
{
    for(; *src; dest++, src++)
        *dest = *src;
    *dest = 0; /* Indicates the end of string */
}

/* The code is fCcked up, brief though */
void string_copy_v2(char *dest, const char *src)
{
    while((*dest++ = *src++));
}

int main()
{
    char msg[] = "C is the most popular programming language! No discussion.";
    char msgcpy[256], msgcpy_v2[256];

    printf("The length is: %d\n", string_len(msg));
    printf("Alternatively: %d\n", string_len_v2(msg));

    string_copy(msgcpy, msg);
    string_copy_v2(msgcpy_v2, msg);

    printf("The lengths of the counterparts are: %d, %d\n",
           string_len(msgcpy),
           string_len(msgcpy_v2));

    return 0;
}
