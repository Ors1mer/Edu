#include <iostream>

int main()
{
    using namespace std;
    long double a, sum = 0;
    int64_t n;

    cout << "Введiть А та N: ";
    cin >> a >> n;
    if(n <= 0)
        throw invalid_argument("N must be greater than 0!");

    long double element = a;
    for (uint64_t i = 1; i <= n; i++) {
        sum += element;
        element *= a*a;
    }
    cout << "The result is " << sum << '\n';
}
