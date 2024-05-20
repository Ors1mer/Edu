/* three_digit_integer.c
 * Determine, weather there is a three-digit integer
 * abc (= 100a + 10b + c) where abc = a! + b! + c!
 */
#include <stdio.h>

int fact(int x)
{
    if(x == 0)
        return 1;
    else
        return x*fact(x-1);
}

int fact_sum(int x, int y, int z)
{
    return fact(x) + fact(y) + fact(z);
}

int main()
{
    int abc = 100;
    for(; abc <= 999; abc++) {
        if(abc == fact_sum(abc/100, abc/10%10, abc%10))
            printf("%d\n", abc);
    }
    return 0;
}
