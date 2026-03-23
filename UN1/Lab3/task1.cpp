#include <iostream>

int main() {
    using std::cout, std::cin;
    setlocale(LC_CTYPE, "UA");
    
    // input variables
    double a, b; 

    cout << "Введіть A та B (A >= B): ";
    cin >> a >> b;
    
    // foolproof
    if (a < b || a <= 0 || b <= 0)
        throw std::invalid_argument("Невірні дані! A має бути >= B та обидва числа більше 0!");

    // the cycle
    do {
        a -= b;
    } while (a >= b);
    
    cout << "Довжина незайнятої частини A дорівнює  " << a << '\n';
}
