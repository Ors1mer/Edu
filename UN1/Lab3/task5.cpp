#include <iostream>

int main()
{
    using std::cout, std::cin;
    uint64_t n, f;
    int fib_seq[2] = {1, 1};

    cout << "Enter the number: ";
    cin >> n;
    if(n <= 1) {
        throw std::invalid_argument("N must be an integer greater than 1!");
    }

    //the cycle
    do {
        f = fib_seq[0] + fib_seq[1];
        if(n == f) {
            cout << "True\n";
            return 0;
        }
        fib_seq[0] = fib_seq[1];
        fib_seq[1] = f;
    } while(f < n);

    cout << "False\n";
}
