#include <iostream>

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");
    
    //declaring input & output variables
    double x, sum;
    int64_t n;
    
    cout << "Введiть X та N: ";
    cin >> x >> n;
    
    //foolproof
    if (x > 1 || x < -1) throw invalid_argument("Невірні дані! |X| має бути < 1!");
    if (n <= 0) throw invalid_argument("Невірні дані! N має бути < 1!");
    
    //diclaring additional variables
    double x_to_pow = x;
    int16_t sign = 1;
    //calculating the Taylor series
    for (uint64_t i = 1; i <= n; i++) {
        sum += sign*x_to_pow/i;

        x_to_pow *= x; sign = -sign;
    }

    cout << "Результат дорiвнює " << sum << '\n';
}
