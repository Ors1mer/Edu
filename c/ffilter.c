/* ffilter.c
 * Three files are given, where only the first one exists. The second file
 * is considered as text and will have only the lines that start with a space
 * form the first file. The third file is treated as a binary and contains the
 * line lengths of the first file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFSIZE 32

int string_len(const char *str)
{
    const char *p;
    for(p = str; *p; p++)
        {}
    return p - str;
}

void open_files(const char **files, FILE **first, FILE **second, int *fd_third)
{
    *first = fopen(files[0], "r");
    if(*first == NULL) {
        perror("Couldn't open the first file");
        exit(2);
    }
    *second = fopen(files[1], "w");
    if(*second == NULL) {
        perror("Couldn't open the second file");
        fclose(*first);
        exit(2);
    }
    *fd_third = open(files[2], O_WRONLY | O_CREAT, 0666);
    if(*fd_third == -1) {
        perror("Couldn't open the third file");
        fclose(*first);
        fclose(*second);
        exit(2);
    }
}

void close_files(FILE *first, FILE *second, int fd_third)
{
    fclose(first);
    fclose(second);
    close(fd_third);
}

int main(int argc, const char **argv)
{
    FILE *first = NULL, *second = NULL;
    int fd_third, err, cnt = 0, has_newline = 0, is_spacestart = 0;
    char buffer[BUFFSIZE];
    if(argc < 4) {
        fprintf(stderr, "Not enough files given!\nMust be three\n");
        return 1;
    }
    open_files(argv+1, &first, &second, &fd_third);
    while(fgets(buffer, sizeof(buffer), first)) {
        if(has_newline) {
            cnt = string_len(buffer);
            is_spacestart = (buffer[0] == ' ') ? 1 : 0;
        } else {
            cnt += string_len(buffer);
        }
        has_newline = (buffer[string_len(buffer)-1] == '\n') ? 1 : 0;
        if(is_spacestart) {
            err = fputs(buffer, second);
            if(err == -1)
                fprintf(stderr, "Failed to write to the second file!\n");
        }
        if(has_newline) {
            err = write(fd_third, &cnt, sizeof(cnt));
            if(err == -1)
                perror("Failed to write to the third file");
        }
    }
    close_files(first, second, fd_third);
    return 0;
}
