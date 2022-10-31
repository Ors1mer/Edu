#include <iostream>
#include <cmath>


int main() {
    using namespace std;
    // input values
    double n, x;
    // output value
    double y;

    cout << "Enter n: ";
    cin >> n;
    cout << "Enter x: ";
    cin >> x;
    
    // calculating in two ways depending on input
    if ((n != 0 && x >= 0) && (n > 0 && n != 1))
        y = log(x) / log(n); // logarithm with custom base
    else
        y = abs(pow(x, n+2));

    cout << "y = "<< y << '\n';
}
