#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    using namespace std;
    double h, r;
    double V, S;
    // Asking for the input files
    cout << "Enter the height of the cone: ";
    cin >> h;
    cout << "Enter the radius of the cone: ";
    cin >> r;
    // Calculations
    V = (1.0/3)*M_PI*pow(r, 2.0)*h;
    S = M_PI*r*(r + sqrt(pow(r, 2.0)+pow(h, 2.0)));
    // Output the result
    cout.setf(ios::fixed);
    cout.precision(5);
    cout << "Volume = " << V << '\n';
    cout << "Total surface area = " << S << '\n';
    cout << endl << r*r*h << endl << sqrt(pow(r, 2.0)+pow(h, 2.0));
}
