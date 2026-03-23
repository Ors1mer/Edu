#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    using namespace std;
    double x, b, a;
    double numerator, denominator, logarithm;
    // Asking for the input values
    cout << "Enter the X number: ";
    cin >> x;
    cout << "Enter the B number: ";
    cin >> b;
    // Calculation
    numerator = (2*x - 3)*pow(7+12*b, 2.0) + x;
    logarithm = log(4*pow(x, 4.0)) / log(3);
    denominator = cos(x)*sqrt(b) - abs(x) + logarithm;
    a = numerator/denominator;
    // Output the result
    cout.setf(ios::fixed);
    cout << "A = " << setprecision(5) << a << '\n';
}
