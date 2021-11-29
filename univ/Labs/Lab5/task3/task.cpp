#include <iostream>

void digitCountSum(uint64_t k, uint16_t &c, uint16_t &s) {
    c = 0, s = 0;
    while (k) {
        c++;
        s += k%10;
        k /= 10;
    }
}

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");
    
    //getting numbers from stanrard input
    cout << "Введiть 5 чисел: ";
    uint64_t nums[5];
    for (short i = 0; i <= 4; i++) cin >> nums[i];

    //getting answers c and s
    uint16_t c, s;
    for (short i = 0; i <= 4; i++) {
        cout << << << ;
    }
}
