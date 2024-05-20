/* server.c
 * The UDP deamon listens to the specified port. Answers with
 * statistics of total packets sent and their total size.
 */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define UDP_PACKET_SIZE 508
#define NOFLAG 0

#define DEMONIZE() \
    close(0); \
    close(1); \
    close(2); \
    open("/dev/null", O_RDONLY); \
    open("/dev/null", O_WRONLY); \
    open("/dev/null", O_WRONLY); \
    chdir("/"); \
    pid = fork(); \
    if(pid > 0) \
        exit(0); \
    setsid(); \
    pid = fork(); \
    if(pid > 0) \
        exit(0)

enum {
    argerr = 1,
    sockerr,
    binderr,
    iperr
};

int string_len(const char *str)
{
    const char *p;
    for(p = str; *p; p++)
        {}
    return p - str;
}

int bind_socket(int sockfd, int ip, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(ip);
    return bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
}

void wait_packet(int sockd, unsigned long *pckcnt, unsigned long *pcksize,
                 struct sockaddr_in *client)
{
    socklen_t tolen;
    char *buff;
    buff = calloc(sizeof(char), UDP_PACKET_SIZE);
    tolen = sizeof(client);

    recvfrom(sockd, buff, sizeof(char)*UDP_PACKET_SIZE, NOFLAG,
             (struct sockaddr*)client, &tolen);
    /* Change the counters */
    (*pckcnt)++;
    *pcksize += string_len(buff);
}

void send_report(int sockd, unsigned long pckcnt, unsigned long pcksize,
                 struct sockaddr_in *client)
{
    char *buff;
    int size;
    buff = calloc(sizeof(char), UDP_PACKET_SIZE);

    size = snprintf(buff, sizeof(char)*UDP_PACKET_SIZE,
                    "Packet count: %lu\nTotal size: %lu\n",
                    pckcnt, pcksize);

    sendto(sockd, buff, size, NOFLAG, (const struct sockaddr*)client,
           sizeof(*client));
    free(buff);
}

int main(int argc, const char **argv)
{
    struct sockaddr_in *client;
    int pid, sockd, errcode;
    unsigned long pckcnt = 0, pcksize = 0;
    client = malloc(sizeof(*client));
    DEMONIZE();
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
        close(sockd);
        return binderr;
    }
    for(;;) {
        wait_packet(sockd, &pckcnt, &pcksize, client);
        send_report(sockd, pckcnt, pcksize, client);
    }
    return 0;
}
