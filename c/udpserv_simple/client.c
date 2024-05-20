/* client.c
 * The program accepts 3 parameters: IP, port, size of string.
 * It sends a random string of the specified size, waits for the answer,
 * then prints it to stdout.
 */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define UDP_PACKET_SIZE 508
#define NOFLAG 0

enum exitcodes {
    argerr = 1,
    sockerr,
    binderr,
    iperr,
    senderr,
    noanserr
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

void print_msg(const char *buff)
{
    puts("---");
    while(*buff) {
        if((*buff < 32 || *buff > 126) && (*buff != '\n' && *buff != '\t'))
            putchar('?');
        else
            putchar(*buff);
        buff++;
    }
    puts("---");
}

char *randomstr(int size)
{
    char *str, *p;
    srand(time(NULL));
    str = malloc(size*sizeof(char));
    for(p = str; p < str+size; p++)
        *p = 1 + (int)(127.0*rand()/(RAND_MAX+1.0)); /* random ASCII symbol */
    return str;
}

int send_str(int sockd, const char *ip, int port, int size)
{
    struct sockaddr_in serv; /* server ip/port address */
    char *str;
    int ok, errcode;

    serv.sin_family = AF_INET;
    ok = inet_aton(ip, &(serv.sin_addr));
    if(!ok)
        return -1;
    serv.sin_port = htons(port);

    size = (size > UDP_PACKET_SIZE) ? UDP_PACKET_SIZE : size;
    str = randomstr(size);

    errcode = sendto(sockd, str, size, NOFLAG, (const struct sockaddr*)&serv,
                     sizeof(serv));
    if(errcode == -1) {
        perror("Sendto error: ");
        free(str);
        exit(senderr);
    }
    free(str);
    return 0;
}

char *wait_answer(int sockd, unsigned int timeout)
{
    struct timeval tv; 
    struct sockaddr from;
    socklen_t tolen;
    char *buff;
    buff = calloc(sizeof(char), UDP_PACKET_SIZE);

    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    setsockopt(sockd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    tolen = sizeof(from);
    recvfrom(sockd, buff, sizeof(char)*UDP_PACKET_SIZE, NOFLAG,
             (struct sockaddr*)&from, &tolen);
    if(!(*buff)) {
        printf("No answer!\n");
        free(buff);
        exit(noanserr);
    }

    return buff;
}

int main(int argc, const char **argv)
{
    int sockd, errcode;
    char *buff;
    if(argc < 4) {
        fprintf(stderr, "Not enough arguments (ip, port, string size)\n");
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
    errcode = send_str(sockd, argv[1], atoi(argv[2]), atoi(argv[3]));
    if(errcode) {
        fprintf(stderr, "Bad IP %s!\n", argv[1]);
        return iperr;
    }
    buff = wait_answer(sockd, 2);
    print_msg(buff);
    free(buff); close(sockd); /* freeing & closing */
    return 0;
}
