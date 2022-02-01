#include <iostream>

int main() {
    using std::cout, std::cin;

    const int N = 9; // The size of the array
    uint32_t Fib[N] = {1, 1};
    cout << Fib[8] << '\n';
    
    // Calculation
    for (int i = 2; i < N; i++) {
        Fib[i] = Fib[i-1] + Fib[i-2];
    }

    // Output
    for (int i = 0; i < N; i++) {
        cout << Fib[i] << '\t';
    }
}
