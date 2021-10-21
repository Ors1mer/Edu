#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "UA");

    // input values
    double n, x;
    // output value
    double y;

    cout << "Введіть n: ";
    cin >> n;
    cout << "Введіть x: ";
    cin >> x;
    
    // calculating in two ways depending on input
    if ((n != 0 && x >= 0) && (n > 0 && n != 1))
        y = log(x) / log(n); // logarithm with custom base
    else
        y = abs(pow(x, n+2));

    cout << "y = "<< y << '\n';
}
