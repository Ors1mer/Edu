/* fscanner.c
 * Get a set of files in form of arguments, where all of them contain 4-byte
 * integers. The last file specified will contain some statistics about the
 * files.
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>

void process_file(const char *file, FILE *statfile)
{
    int fd, max = INT_MIN, min = INT_MAX, cnt = 0;
    fd = open(file, O_RDONLY);
    if(fd == -1) {
        perror(file);
        exit(3);
    }
    for(;;) {
        int err, val;
        err = read(fd, &val, sizeof(val));
        if(err == -1)
            perror(file);
        else if(err == 0)
            break;
        cnt++;
        if(val > max)
            max = val;
        if(val < min)
            min = val;
    }
    fprintf(statfile, "%s %i %i %i\n", file, cnt, min, max);
    close(fd);
}

int main(int argc, const char **argv)
{
    const char **p;
    FILE *statfile;
    if(argc < 3) {
        fprintf(stderr,
                "Give at least one binary and the file to store the data!\n");
        return 1;
    }

    statfile = fopen(argv[argc-1], "w");
    if(statfile == NULL) {
        perror(argv[argc-1]);
        return 2;
    }

    for(p = argv+1; p != argv+argc-1; p++)
        process_file(*p, statfile);

    fclose(statfile);
    return 0;
}
