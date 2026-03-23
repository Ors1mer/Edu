#include <iostream>

int main() {
    using std::cout, std::cin;

    const size_t M = 1, N = 1;
    int64_t K[M][N] = {{-24}}; 

    // Smallest in row
    cout << "Smallest in row: \t";
    int64_t smallest;
    for (int y = 0; y < M; y++) {
        smallest = K[y][0];
        for (int x = 1; x <= N; x++) {
            if (K[y][x] < smallest) {
                smallest = K[y][x];
            }
        }
        cout << smallest << '\t';
    }

    // Biggest in column
    cout << "\nBiggest in column: \t";
    int64_t biggest;
    for (int x = 0; x < N; x++) {
        biggest = K[0][x];
        for (int y = 1; y < M; y++) {
            if (K[y][x] > biggest) {
                biggest = K[y][x];
            }
        }
        cout << biggest << '\t';
    }
    cout << '\n';
}
