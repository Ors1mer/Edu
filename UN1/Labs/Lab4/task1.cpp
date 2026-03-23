#include <iostream>

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");
    
    int64_t a, b, k, S = 0;

    cout << "Введiть числа А та В (А < В) та дiльник K: ";
    cin >> a >> b >> k;
    
    if (a >= b) {
        throw std::invalid_argument("Невірні дані! A має бути < B!");
    }

    for (int64_t i = a; i <= b; i++) {
        cout << "Для i = " << i << ": " << i%k << '\n';
        S += i%k;
    }

    cout << "Сума остач вiд дiлення: " << S << '\n';
}
