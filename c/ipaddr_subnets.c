/* ipaddr_subnets.c
 * The program expects one argument, IPv4 address,
 * of the format x.x.x.x, where x is 0 through 255.
 * It prints all 32 subnets to which the IP belongs.
 */
#include <stdio.h>
#include <stdlib.h> /* for atoi */

#define ADDR_BYTE_SIZE (4*8)
#define MAXPREFIX ADDR_BYTE_SIZE

typedef unsigned char addr_t[ADDR_BYTE_SIZE];

int string_len(const char *str)
{
    const char *p;
    for(p = str; *p; p++)
        {}
    return p - str;
}

void getocts(addr_t ip, const char *str)
{
    char octstr[4];
    const char *strend = str + string_len(str);

    for(; str < strend; str++) {
        int i = 0;
        while(*str && *str != '.') {
            octstr[i] = *str;
            str++;
            i++;
        }
        octstr[i] = 0;
        *ip = atoi(octstr);
        ip++;
    }
}

int main(int argc, char **argv)
{
    addr_t ip;
    short i = 3, prefix = MAXPREFIX;

    if(argc < 2) {
        fprintf(stderr, "You didn't provide an IP address\n");
        exit(1);
    }

    getocts(ip, argv[1]);

    for(; prefix >= 0; prefix--) {
        printf("%d.%d.%d.%d\\%d\n", ip[0], ip[1], ip[2], ip[3], prefix);
        if(prefix < MAXPREFIX && !(prefix % 8))
            i--;
        ip[i] &= ~(1 << ((MAXPREFIX-prefix) % 8));
    }

    return 0;
}
