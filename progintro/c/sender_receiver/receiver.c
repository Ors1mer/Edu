/* receiver.c
 * The program awaits UDP packets on specified port (as command line parameter)
 * For each received packet it prints the IP & port of the sender, and the
 * message transferred.
 */


#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define UDP_PACKET_SIZE 508
#define NOFLAG 0

enum {
    argerr = 1,
    sockerr,
    binderr,
    iperr
};

/* String operations */
int string_len(const char *str)
{
    const char *p;
    for(p = str; *p; p++)
        {}
    return p - str;
}

void strncopy(char *dest, const char *src, int n)
{
    const char *srcend = src + n;
    for(; *src && src < srcend; dest++, src++)
        *dest = *src;
}

void memflush(char *src, int n)
{
    const char *end = src + n;
    for(; src < end; src++)
        *src = 0;
}

int bind_socket(int sockfd, int ip, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(ip);
    return bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
}
/* End */

void print_datagram(const char *buff)
{
    puts("The message:\n---");
    while(*buff) {
        if((*buff < 32 || *buff > 126) && (*buff != '\n' && *buff != '\t'))
            putchar('?');
        else
            putchar(*buff);
        buff++;
    }
    puts("\n---\n"); /* double newline in the end */
}

void capture_data(int sockd)
{
    char buff[UDP_PACKET_SIZE];
    char ipstr[17];
    struct sockaddr_in addr;
    socklen_t fromlen = sizeof(addr);
    for(;;) {
        recvfrom(sockd, buff, sizeof(buff), NOFLAG, (struct sockaddr*)&addr,
                 &fromlen);
        strncopy(ipstr, inet_ntoa(addr.sin_addr), sizeof(ipstr));
        printf("The sender's address: %s\n", ipstr);
        printf("The sender's port: %d\n", addr.sin_port);
        print_datagram(buff);
        memflush(buff, sizeof(buff));
        memflush(ipstr, sizeof(ipstr));
    }
}

int main(int argc, const char **argv)
{
    int sockd, errcode;
    if(argc < 2) {
        fprintf(stderr, "Not enough arguments!\n");
        return argerr;
    }
    sockd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockd < 0) {
        fprintf(stderr, "Couldn't create the socket!\n");
        return sockerr;
    }
    errcode = bind_socket(sockd, INADDR_ANY, atoi(argv[1]));
    if(errcode == -1) {
        fprintf(stderr, "Couldn't bind the socket with port %s!\n", argv[2]);
        return binderr;
    }
    capture_data(sockd); /* and print it */    
    /* The program won't get to this point - should be killed by SIGINT */
    close(sockd); /* close the only socket descriptor */
    return 0;
}
