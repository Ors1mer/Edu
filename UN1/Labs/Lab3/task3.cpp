#include <iostream>

int main() {
    using std::cout, std::cin;
    setlocale(LC_CTYPE, "UA");

    //input variable
    double a;
    //output variables
    double k = 2;
    double r = 0.5; // summing result
    
    cout << "Введіть значення А: ";
    cin >> a;

    //foolproof
    if (a <= 1) {
        throw std::invalid_argument("А має бути більше 1");
    }

    //the cycle
    while ((r + (k/(k+1))) < a) {
        r += k/(k+1);
        k++;
    }

    cout << "K = " << --k << "\nСума = " << r << '\n';
}
