#include <iostream>

int64_t max(const int64_t &a, const int64_t &b) {
    return a > b ? a : b;
}

long double max(const long double &a, const long double &b) {
    return a > b ? a : b;
}

template <typename num>
num max(const num  &a, const num &b) {
    return a > b ? a : b;
}

int main() {
    using std::cout, std::cin;
    setlocale(LC_CTYPE, "UA");

    long double a, b;
    cout << "Введiть два числа: ";
    cin >> a >> b;

    cout << max(a, b);
}