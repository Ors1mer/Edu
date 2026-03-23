#include <iostream>

int main()
{
    using namespace std;
    int64_t n;
    long double a1 = 1.0, a2 = 2.0, ak;

    cout << "Enter N: ";
    cin >> n;
    if(n <= 1)
        throw invalid_argument("N must be > 1!");

    cout << a1 << ", " << a2;
    if (n >= 3) cout << ", ";

    // Calculating
    for (uint64_t i = 3; i <= n; i++) {
        ak = (a1 + 2*a2)/3;
        cout << ak;
        a1 = a2; a2 = ak;
        if (i != n) cout << ", ";
    }
    cout << '\n';
}
