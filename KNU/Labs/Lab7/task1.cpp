#include <iostream>

int main() {
    using std::cout, std::cin;
    

    const size_t size = 10;
    uint32_t M[size] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

    const size_t N = 1;
    uint32_t matrix[size][N];

    // Print the array
    for (uint32_t elem: M) {
        cout << elem << '\t';
    }
    cout << "\n\n";

    // Filling up the matrix
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < N; x++) {
            matrix[y][x] = M[y];
        }
    }

    // Print the matrix
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < N; x++) {
            cout << matrix[y][x] << '\t';
        }
        cout << '\n';
    }
}
