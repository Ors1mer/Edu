#include <iostream>

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");

    int64_t n;
    int16_t sign = 1;
    long double res = 1.1;

    cout << "Введiть значення N: ";
    cin >> n;

    if (n <= 0) throw invalid_argument("Невірні дані! N має бути > 0!");

    cout << res;
    long double element = 1.1;
    for (uint64_t i = 2; i <= n; i++) {
        element += 0.1;
        cout << showpos << sign*element;
        res += sign*element;
        sign = -sign;
    }

    cout << "\nРезультат дорiвнює " << noshowpos << res << '\n';

}
