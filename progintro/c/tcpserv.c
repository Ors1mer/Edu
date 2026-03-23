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

#define NOFLAG 0
#define QLEN 128
#define PACKET_SIZE 150

#define DAEMONIZE() \
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

#define HANDLE_ERR_CLOSE(errcode, sockd, msg, errexit) \
    if(errcode == -1) { \
        perror(msg); \
        close(sockd); \
        return errexit; \
    }

enum {
    argerr = 1,
    sockerr,
    binderr,
    iperr,
    listenerr,
    senderr
};

void strncopy(char *dest, const char *src, int n)
{
    const char *srcend = src + n;
    for(; *src && src < srcend; dest++, src++)
        *dest = *src;
}

char *write_date(char *dest, unsigned int size)
{
    size_t len;
    time_t current;
    current = time(NULL);
    len = strftime(dest, size, "Timestamp: %x %I:%M %p\n",
                   localtime(&current));
    /* return pointer to the end of string */
    return dest + len;
}

char *fill_buffer(const struct sockaddr_in *addr, size_t *buffsize)
{
    char *buff, *curr_p;
    char ipstr[16];
    int len;
    unsigned short port;
    buff = calloc(sizeof(char), PACKET_SIZE);

    curr_p = write_date(buff, PACKET_SIZE);

    port = ntohs(addr->sin_port);
    strncopy(ipstr, inet_ntoa(addr->sin_addr), sizeof(ipstr));

    len = snprintf(curr_p, PACKET_SIZE-(curr_p-buff), "IP: %s\nPort: %d\n",
                   ipstr, port);
    curr_p += len;

    *buffsize = curr_p - buff;
    return buff;
}

int bind_socket(int sockd, unsigned int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;    
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    return bind(sockd, (struct sockaddr*)&addr, sizeof(addr));
}

unsigned short get_port(const char *strport)
{
    unsigned short port;
    port = atoi(strport);
    if(port == 0) {
        fputs("The port must be a number between 1024 and 65535!\n", stderr);
    } else if(port < 1024) {
        fputs("A privileged port specified (port < 1024)!\n", stderr);
        return 0;
    }
    return port;    
}

void answer_clients(int server_sockd)
{
    int client_sockd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    for(;;) {
        size_t buffsize;
        char *buff;
        client_sockd = accept(server_sockd, (struct sockaddr*)&addr, &addrlen);
        
        buff = fill_buffer(&addr, &buffsize);

        write(client_sockd, buff, buffsize);

        free(buff);
        shutdown(client_sockd, SHUT_RDWR);
        close(client_sockd);
    }
}

int main(const int argc, const char **argv)
{
    int sockd, errcode, option, pid;
    unsigned short port;
    if(argc < 2) {
        fputs("Not enough arguments: no port specified!\n", stderr);
        return argerr;
    }
    port = get_port(argv[1]);
    if(port == 0)
        return argerr;
    sockd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockd == -1) {
        perror("Socket error");
        return sockerr;
    }
    /* solve sticky tcp port problem */
    setsockopt(sockd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    errcode = bind_socket(sockd, port);
    HANDLE_ERR_CLOSE(errcode, sockd, "Error binding socket", binderr)
    errcode = listen(sockd, QLEN);
    HANDLE_ERR_CLOSE(errcode, sockd, "Error setting listen state", sockerr);
    DAEMONIZE();
    answer_clients(sockd);
    close(sockd);
    return 0;
}

