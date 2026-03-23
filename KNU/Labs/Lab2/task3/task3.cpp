#include <iostream>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "UA"); 

    // input values
    double a, b, c;
    // additional variable
    double t;

    cout << "Введіть a, b, c: ";
    cin >> a >> b >> c;

    if ((a<b && b<c) || (c<b && b<a)) {
        t = b; b = a; a = t;
    } else if ((a<c && c<b) || (b<c && c<a)) {
        t = c; c = a; a = t;
    }

    cout << "A = " << a << '\n';
    cout << "B = " << b << '\n';
    cout << "C = " << c << '\n';
    }
