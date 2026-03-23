#include <iostream>

int main() {
    using std::cout, std::cin;

    //input variable
    uint64_t n, f;
    int fib_seq[2] = {1, 1};

    cout << "Enter the number: ";
    cin >> n;

    //foolproof
    if (n <= 1) {
        throw std::invalid_argument("N має бути натуральним числом більшим за 1!");
    }

    //the cycle
    do {
        f = fib_seq[0] + fib_seq[1];

        if (n == f) {
            cout << "True\n";
            return 0;
        }
        
        fib_seq[0] = fib_seq[1];
        fib_seq[1] = f;
    } while (f < n);

    cout << "False\n";
}
