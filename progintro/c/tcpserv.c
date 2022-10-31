/* tcpserv.c
 * The TCP server awaits a connection, then sends to the client
 * current timedate and the client's public IP. Then breaks the connection.
 * The server answers to the clients one by one.
 */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
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

#define HANDLE_ERR_CLOSE(errcode, msg, sockd, errexit) \
    if(errcode == -1) { \
        perror(msg); \
        close(sockd); \
        return errcode; \
    }

enum {
    argerr = 1,
    sockerr,
    binderr,
    iperr,
    listenerr,
    senderr
};


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


int bind_socket(int sockfd, int ip, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(ip);
    return bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
}


char *write_date(char *dest)
{
    size_t len;
    time_t current;
    current = time(NULL);
    len = strftime(dest, UDP_PACKET_SIZE, "Timestamp: %x %I:%M %p\n",
                   localtime(&current));
    /* return pointer to the end of string */
    return dest + len;
}

char *fill_buff(const struct sockaddr_in *addr, size_t *buffsize)
{
    char *buff, *curr_p;
    char ipstr[16];
    int len;
    buff = calloc(sizeof(char), UDP_PACKET_SIZE);

    curr_p = write_date(buff);

    strncopy(ipstr, inet_ntoa(addr->sin_addr), sizeof(ipstr));
    len = snprintf(curr_p, UDP_PACKET_SIZE-(curr_p-buff), "IP: %s\n", ipstr);
    curr_p += len;

    *buffsize = curr_p - buff;
    return buff;
}

void answer_clients(int sockd)
{
    struct sockaddr_in client;
    socklen_t addrsize = sizeof(client);
    int sockd_client, errcode;
    for(;;) {
        char *buff;
        size_t size;
        sockd_client = accept(sockd, (struct sockaddr*)&client, &addrsize);

        buff = fill_buff(&client, &size);

        errcode = sendto(sockd_client, buff, size, NOFLAG,
                         (const struct sockaddr*)&client, addrsize);
        if(errcode == -1)
            perror("sendto");
        free(buff);
        shutdown(sockd_client, SHUT_RDWR);
        close(sockd_client);
    }
}

int main(int argc, const char **argv)
{
    int pid, sockd, errcode, opt = 1;
    #ifndef DEBUG
    DEMONIZE();
    #endif
    if(argc < 2) {
        fprintf(stderr, "No port specified!\n");
        return argerr;
    }
    sockd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockd < 0) {
        fprintf(stderr, "Couldn't create the socket!\n");
        return sockerr;
    }
    setsockopt(sockd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    errcode = bind_socket(sockd, INADDR_ANY, atoi(argv[1]));
    HANDLE_ERR_CLOSE(errcode, "bind", sockd, binderr);

    errcode = listen(sockd, 128);
    HANDLE_ERR_CLOSE(errcode, "listen", sockd, listenerr);

    answer_clients(sockd);

    return 0;
}
