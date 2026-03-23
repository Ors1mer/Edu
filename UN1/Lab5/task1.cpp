#include <iostream>

long double circle_area(long double r)
{
    return 3.1415926*r*r;
}

int main()
{
    using namespace std;
    long double r1, r2, r3;
    cout << "Enter the radiuses: ";
    cin >> r1 >> r2 >> r3;

    cout << "Areas:\n" << "S1 = " << circle_area(r1) << '\n';
    cout << "S2 = " << circle_area(r2) << '\n';
    cout << "S3 = " << circle_area(r3) << '\n'; 
}
