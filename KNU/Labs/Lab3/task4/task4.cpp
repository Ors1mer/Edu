#include <iostream>

int main() {
    using std::cout, std::cin;
    setlocale(LC_CTYPE, "UA");

    //input & output variables
    uint64_t n;

    cout << "Введіть число N: ";
    cin >> n;
    
    //foolproof
    if (n == 0) {
        throw std::invalid_argument("N має бути натуральним числом!");
    }

    cout << "Число при читанні зліва направо: ";
    //output every last digit one by one until n isn't zero
    while (n) {
        cout << n%10;
        n /= 10;
    }
    cout << '\n';
}
