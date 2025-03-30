/* xor_encryptor.c
 *
 */
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define BUFFSIZE 4096

char get_byte(int value, short n)
{
    return (char)((value >> 8*(n-1)) & 0xff);
}

void encrypt(int fd, int key, const char *fname)
{
    char buffer[BUFFSIZE];
    for(;;) {
        int n = 1, cnt;
        char *p;

        cnt = read(fd, buffer, BUFFSIZE);
        if(cnt == -1) {
            perror(fname);
            break;
        } else if(cnt == 0) {
            break;
        }

        for(p = buffer; p<buffer+cnt; p++) {
            *p ^= get_byte(key, n);
            n = (n > 4) ? 1 : n+1;
        }

        lseek(fd, -cnt, SEEK_CUR);
        write(fd, buffer, cnt);
        lseek(fd, cnt, SEEK_CUR);
    }
}

int main(int argc, const char **argv)
{
    int key, fd;
    if(argc < 3) {
        fprintf(stderr, "Specify a file and an encryption key "
                "(non-zero positive integer)\n");
        return 1;
    }
    key = atoi(argv[2]);
    if(key == 0) {
        fprintf(stderr, "Specify a non-zero positive integer as the second "
                "argument\n");
        return 2;
    }
    fd = open(argv[1], O_RDWR);
    if(fd == -1) {
        perror(argv[1]);
        return 3;
    }
    encrypt(fd, key, argv[1]);
    fdatasync(fd);
    close(fd);
    return 0;
}
