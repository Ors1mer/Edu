#include <iostream>

int main()
{
    using namespace std;
    double x, sum;
    int64_t n;

    cout << "Enter X & N: ";
    cin >> x >> n;
    if(x > 1 || x < -1)
        throw invalid_argument("|X| must be < 1!");
    if(n <= 0)
        throw invalid_argument("N must be < 1!");

    double x_to_pow = x;
    int16_t sign = 1;
    // Calculating the Taylor series
    for (uint64_t i = 1; i <= n; i++) {
        sum += sign*x_to_pow/i;
        x_to_pow *= x; sign = -sign;
    }
    cout << "The result is " << sum << '\n';
}
