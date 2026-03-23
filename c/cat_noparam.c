/* cat_noparam.c
 * Acts like cat without parameters.
 */
#include <unistd.h>
#define BLOCKSIZE 4096
int main()
{
    int count;
    char buffer[BLOCKSIZE];
    while((count = read(0, buffer, BLOCKSIZE)) > 0) {
        write(1, buffer, count);
    }
    return 0;
}
