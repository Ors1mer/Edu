#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

// the studied function
long double func(long double x) {
    return (exp(-x) + 1);
}

// calculate exact result via Newton-Leibniz formula
long double Newton_Leibniz(long double a, long double b) {
    return ( (-exp(-b) + b) - (-exp(-a) + a) );
}

// calculate result via midpoint rectangles method
long double rectangles_method(uint16_t n, long double a, long double b) {
    long double result = 0;
    long double delta = (b-a)/n;

    for (int i = 0; i < n; i++) {
        result += func(a + delta/2)*delta;
        a += delta;
    }

    return result;
}

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");

    // arguments of the function, the range of calculation
    long double a, b;
    ifstream fin("input1.in");
    if (!fin) cerr << "Файл порожній або не існує";
    fin >> a >> b;
    // variables to save calculated function values
    long double rm;
    long double nl = Newton_Leibniz(a, b);

    //define the output file
    ofstream fout("out1.txt");

    //make cout/fout always print 8 digits after point
    cout.setf(ios::fixed);
    cout.precision(8);
    fout.setf(ios::fixed);
    fout.precision(8);


    cout << "Підінтегральна функція y = e^-x + 1\nПроміжок ["<<a<<", "<<b<< "]\n"
         << "Точне значення інтегралу на проміжку: " << nl << '\n';
    fout << "Підінтегральна функція y = e^-x + 1\nПроміжок ["<<a<<", "<<b<< "]\n"
         << "Точне значення інтегралу на проміжку: " << nl << '\n';

    for (uint16_t n = 10; n <= 100; n += 5) {
        rm = rectangles_method(n, a, b);

        cout << "n = " << n << '\t' << rm << "  "
             << Newton_Leibniz(a, b) - rm << '\n';
        fout << "n = " << n << '\t' << rm << "  "
             << Newton_Leibniz(a, b) - rm << '\n';
    }

    fin.close(); fout.close();
}
