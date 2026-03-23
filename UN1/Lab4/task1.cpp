#include <iostream>

int main()
{
    using namespace std;
    int64_t a, b, k, S = 0;

    cout << "Enter А & В (А < В) and the denominator K: ";
    cin >> a >> b >> k;
    if(a >= b) {
        throw std::invalid_argument("A must be less than B!");
    }

    for(int64_t i = a; i <= b; i++) {
        cout << "For i = " << i << ": " << i%k << '\n';
        S += i%k;
    }
    cout << "The sum of the remainders: " << S << '\n';
}
