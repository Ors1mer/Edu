#include <iostream>

int main() {
    using std::cout, std::cin;
    setlocale(LC_CTYPE, "UA");

    // input variables
    double P;                 // percent
    uint64_t M;               // total max kilometers
    // other variables
    uint64_t K = 1;           // days
    double S = 10.0;          // kilometers total

    cout << "Введіть відсоток приросту забігів та необхідну відстань: ";
    cin >> P >> M;
    
    // foolproof
    if ((P >= 50) || (P <= 0)) {
        throw std::invalid_argument("Має виконуватися умова 0 < P < 50");
    }

    // the cycle
    while (S <= M) {
        S += S*P*0.01;
        K++;
    }
    
    cout << "Сумарний пробіг: " << S << "\nДнів: " << K << '\n';
}
