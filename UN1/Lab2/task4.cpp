#include <iostream>
#include <cmath>


int main() {
    using namespace std;
    // input variables
    int n;
    double x;
    // output variables
    double r, d, l, s;
    
    cout << "Enter the number and the value: ";
    cin >> n >> x;

    switch (n) {
        case 1:
            r = x;
            cout << r << endl;
            d = 2*r;
            l = M_PI*d;
            s = M_PI*pow(r, 2);
            break;
        case 2:
            d = x;
            r = d/2;
            l = M_PI*d;
            s = M_PI*pow(r, 2);
            break;
        case 3:
            l = x;
            d = l/M_PI;
            r = d/2;
            s = M_PI*pow(r, 2);
            break;
        case 4:
            s = x;
            r = sqrt(s/M_PI);
            d = 2*r;
            l = M_PI*d;
            break;
    }
    
    cout << "R = " << r << '\n';
    cout << "D = " << d << '\n';
    cout << "L = " << l << '\n';
    cout << "S = " << s << '\n';
}
