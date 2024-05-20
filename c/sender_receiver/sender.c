/* sender.c
 * The program accepts 3 parameters: IP, port, string.
 * It sends the string to the specified address.
 */

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define UDP_PACKET_SIZE 508
#define NOFLAG 0

enum exitcodes {
    argerr = 1,
    sockerr,
    binderr,
    iperr,
    senderr
};

int bind_socket(int sockfd, int port, int ip)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(ip);
    return bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
}

int string_len(const char *str)
{
    const char *p;
    for(p = str; *p; p++)
        {}
    return p - str;
}

int send_str(int sockd, const char *ip, int port, const char *str)
{
    struct sockaddr_in recv; /* receiver's ip/port address */
    const char *strend;
    int ok, errcode;
    strend = str + string_len(str);
    recv.sin_family = AF_INET;
    ok = inet_aton(ip, &(recv.sin_addr));
    if(!ok)
        return -1;
    recv.sin_port = htons(port);

    while(str < strend) {
        if(strend - str < UDP_PACKET_SIZE) {
            errcode = sendto(sockd, str, strend - str, NOFLAG,
                   (const struct sockaddr*)&recv, sizeof(recv));
        } else {
            errcode = sendto(sockd, str, UDP_PACKET_SIZE, NOFLAG,
                   (const struct sockaddr*)&recv, sizeof(recv));
        }
        if(errcode == -1) {
            perror("Sendto error: ");
            exit(senderr);
        }
        str += UDP_PACKET_SIZE;
    }
    return 0;
}

int main(int argc, const char **argv)
{
    int sockd, errcode;
    if(argc < 4) {
        fprintf(stderr, "Not enough arguments!\n");
        return argerr;
    }
    sockd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockd < 0) {
        fprintf(stderr, "Couldn't create the socket!\n");
        return sockerr;
    }
    errcode = bind_socket(sockd, 0, INADDR_ANY); /* bind to any socket */
    if(errcode == -1) {
        fprintf(stderr, "Couldn't bind the socket with port %s!\n", argv[2]);
        return binderr;
    }
    errcode = send_str(sockd, argv[1], atoi(argv[2]), argv[3]);
    if(errcode) {
        fprintf(stderr, "Bad IP %s!\n", argv[1]);
        return iperr;
    }
    close(sockd); /* close the only socket descriptor */
    return 0;
}
