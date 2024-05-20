/* less_simple_tcpserv.c
 * The TCP server reads client's text and answers "Ok". The session continues
 * until the user breaks it. The server has no restrictions on the number of
 * users connected.
 */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#define QLEN 128
#define MSG "Ok\n"
#define MSG_SIZE 4 /* bytes */

#define TIMEOUT_SEC 5
#define TIMEOUT_USEC 0

#define HANDLE_ERR_CLOSE(errcode, sockd, msg, errexit) \
    if(errcode == -1) { \
        perror(msg); \
        close(sockd); \
        return errexit; \
    }

enum errcodes {
    argerr = 1,
    sockerr,
    binderr,
    iperr,
    listenerr,
};

struct llist {
    int fd; /* descriptor's number */
    struct llist *next;
};

void daemonize()
{
    int pid;
    close(0); 
    close(1);
    close(2);
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_WRONLY);
    chdir("/");
    pid = fork();
    if(pid > 0)
        exit(0);
    setsid();
    pid = fork();
    if(pid > 0)
        exit(0);
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


void main_loop(int ls)
{
    struct llist *fd_first = NULL, *fd_ptr;
    struct timeval timeout;
    for(;;) {
        int errcode, fd, maxfd = ls;
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(ls, &readfds);
        for(fd_ptr = fd_first; fd_ptr->next != NULL; fd_ptr = fd_ptr->next) {
            FD_SET(fd_ptr->fd, &readfds);
            maxfd = fd_ptr->fd > maxfd ? fd_ptr->fd : maxfd;
        }
        timeout.tv_sec = TIMEOUT_SEC;
        timeout.tv_usec = TIMEOUT_USEC;

        errcode = select(maxfd+1, &readfds, NULL, NULL, &timeout);
        if(errcode == -1) { /* an error occurred */
            if(errno == EINTR) { /* a signal */

            } else { /* a select error */

            }
            continue;
        } else if(errcode == 0) { /* timeout */
            continue;
        }
        if(FD_ISSET(ls, &readfds)) { /* a new client connected */

        }
        for(fd_ptr = fd_first; fd_ptr->next != NULL; fd_ptr = fd_ptr->next) {
            if(FD_ISSET(fd_ptr->fd)) {
                /* read data and answer OK, beware of EOF */
            }
        }
    }
}

int main(const int argc, const char **argv)
{
    int sockd, errcode, option;
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
    HANDLE_ERR_CLOSE(errcode, sockd, "Error setting listen state", listenerr);
    daemonize();
    main_loop(sockd);
    close(sockd);
    return 0;
}

