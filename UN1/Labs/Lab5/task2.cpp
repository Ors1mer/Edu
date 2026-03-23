#include <iostream>

bool IsPrime(uint64_t n) {
    for (uint64_t i = 2; i < n; i++) {
        if (!(n%i)) return false;
    }
    return true;
}

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");

    uint64_t n;
    uint16_t count = 0;

    cout << "Введiть 10 чисел бiльше 1: ";
    for (uint16_t i = 0; i <= 9; i++) {
        cin >> n;
        if (n < 2) throw invalid_argument("Невірні дані! N має бути бiльше 2!");
        if (IsPrime(n)) count++;
    }

    cout << "Кiлькiсть простих чисел: " << count << '\n';
}
