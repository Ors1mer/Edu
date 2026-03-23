#include <iostream>

bool IsPrime(uint64_t n)
{
    for (uint64_t i = 2; i < n; i++) {
        if (!(n%i))
            return false;
    }
    return true;
}

int main()
{
    using namespace std;
    uint64_t n;
    uint16_t count = 0;

    cout << "Enter 10 greater than 1: ";
    for(uint16_t i = 0; i <= 9; i++) {
        cin >> n;
        if(n < 2)
            throw invalid_argument("N must be > 2!");
        if(IsPrime(n))
            count++;
    }

    cout << "The amount of prime numbers: " << count << '\n';
}
