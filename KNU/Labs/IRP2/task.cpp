#include <iostream>
#include <cmath>
#include <iomanip>

const double eps = 1e-3;

//iterable solution

long double iter_cos(long double x) {
    long double sum = 1, element = 1;
    int16_t sign = -1;
    uint32_t n = 2;
    while (fabs(element) > eps) {
        element *= x*x/(n*(n - 1));
        sum += sign*element;
        
        sign = -sign;
        n += 2;
    }
    return sum;
}

//recursive solution

long double Sum(long double a, long double b, long double x) {
    if (fabs(a/b) > eps) {
        return a/b + Sum(a*-x*x, b*(b+1)*(b+2), x);
    } else {
        return 0;
    }
}

long double recur_cos(long double x) {
    return 1 + Sum(-x*x, 2, x);
}

//tabulation

void full_tabula(long double a, long double b, int n) {
    using namespace std;
    long double dx = (b-a)/n;
    long double x = a + dx;

    cout << 'x' <<"\t\t"<< "iter_cos(x)" <<'\t'<< "recur_cos(x)" <<'\t'<< "cos(x)" <<'\n';
    cout << fixed << setprecision(6);
    while (x < b) {
        cout << x <<'\t'<< iter_cos(x) <<'\t'<< recur_cos(x) <<'\t'<< cos(x) <<'\n';
        x += dx;
    }
}

void tabula(long double a, long double b, int n, long double (*func)(long double)) {
    using namespace std;
    long double dx = (b-a)/n;
    long double x = a + dx;

    cout << 'x' <<"\t\t"<< "func(x)\n";
    cout << fixed << setprecision(6);
    while (x < b) {
        cout << x <<'\t'<< func(x) << '\n';
        x += dx;
    }
}



int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");

    full_tabula(-1, 1, 20);
    tabula(-1, 1, 20, recur_cos);

    return 0;
}
