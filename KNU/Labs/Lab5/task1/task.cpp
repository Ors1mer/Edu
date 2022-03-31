#include <iostream>

long double circleS(long double r) {
    return 3.1415926*r*r;
}

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");

    long double r1, r2, r3;
    cout << "Введiть радiуси кругiв: ";
    cin >> r1 >> r2 >> r3;

    cout << "Площi кругiв:\n" << "S1 = " << circleS(r1) << '\n';
    cout << "S2 = " << circleS(r2) << '\n';
    cout << "S3 = " << circleS(r3) << '\n'; 
}
