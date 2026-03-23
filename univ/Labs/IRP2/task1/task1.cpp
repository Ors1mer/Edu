#include <iostream>

uint64_t factorial(uint32_t n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}


int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");


}
