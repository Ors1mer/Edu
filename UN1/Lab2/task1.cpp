#include <iostream>
#include <cmath>

int main()
{
    using namespace std;
    double n, x, y;

    cout << "Enter n: ";
    cin >> n;
    cout << "Enter x: ";
    cin >> x;
    // Calculating in two ways depending on input
    if ((n != 0 && x >= 0) && (n > 0 && n != 1))
        y = log(x) / log(n); // logarithm with custom base
    else
        y = abs(pow(x, n+2));

    cout << "y = "<< y << '\n';
}
