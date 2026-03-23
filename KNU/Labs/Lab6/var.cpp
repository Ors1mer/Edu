#include <iostream>

int main() {
    using std::cin, std::cout;

    uint16_t c = 7;
    uint16_t secretcode = 3;

    int V = ((c + secretcode) % 5) ? (c + secretcode) % 5 : 5;
    cout << V;
}
