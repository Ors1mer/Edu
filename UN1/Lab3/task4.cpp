#include <iostream>

int main()
{
    using std::cout, std::cin;
    uint64_t n;

    cout << "Enter N: ";
    cin >> n;
    if(n == 0) {
        throw std::invalid_argument("N must be a positive integer!");
    }

    cout << "The reversed number: ";
    // Output every last digit one by one until n isn't zero
    while(n) {
        cout << n%10;
        n /= 10;
    }
    cout << '\n';
}
