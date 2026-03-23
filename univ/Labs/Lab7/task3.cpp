#include <iostream>

int main() {
    using std::cout, std::cin;

    const size_t M = 3, N = 4;
    int64_t K[M][N] = {{-24, 18, 5, 21}, 
                       {-15, -4, -5, 1}, 
                       {48, -64, 33, 12}};

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

}
