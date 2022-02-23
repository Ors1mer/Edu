#include <iostream>

int main() {
    using std::cout, std::cin;

    // Getting the range [a, b]
    int64_t a, b;
    cout << "Enter the a and b: ";
    cin >> a >> b;

    // Creating the matrix
    const size_t R = 3, Q = 4;
    int64_t N[R][Q] = {{-24, 18, 5, 21}, 
                       {-15, -4, -5, 1}, 
                       {48, -64, 33, 12}};

    // Summing odd numbers
    int64_t odd_sum = 0;
    for (int y = 0; y < R; y++) {
        for (int x = 0; x < Q; x++) {
           if (N[y][x]%2 && N[y][x] >= a && N[y][x] <= b) {
               odd_sum += N[y][x];
           } 
        }
    }

    cout << odd_sum << '\n';
}
