#include <iostream>
#include <cmath>

const double eps = 1e-3;

long double iter_cos(long double x) {
    long double sum = 1, element = 1;
    int16_t sign = -1;
    uint32_t n = 1;
    while (fabs(element) > eps) {
        element *= sign*(x*x)/(2*n*(2*n - 1));
        std::cout << element << ' ' << 2*n*(2*n-1) << ' ' <<sign*x*x << '\n';
        sum += element;
        sign = -sign;
        ++n;
    }
    return sum;

}

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");

    long double x;
    cout << "Введiть значення аргументу: ";
    cin >> x;

    cout << iter_cos(x) << '\n';


}
