#include <iostream>

int main() {
    using std::cout, std::cin;

    size_t M = 3, N = 4;

    int64_t matrix [M][N] = {{3, 2, 4, 6},
                             {4, -4, -4, 4},
                             {5, 5, 5, 5}};

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            cout << matrix[y][x] << '\t';
        }
        cout << '\n';
    }
    cout << '\n';

    // Amount of repeating elements are stored in these vars
    int64_t row_max = 0, row_count, el_count;
    int irow_max = 0; // index

    for (int y = 0; y < M; y++) {
        row_count = 0;

        // Iterating each row
        for (int x = 0; x < N; x++) {
            el_count = 0;

            // Counting max amount of repeating elements
            for (int z = x+1; z < N; z++) {
                if (matrix[y][z] == matrix[y][x]) {
                    el_count++;
                }
            }
            if (row_count < el_count) {row_count = el_count;}
        }

        if (row_max <= row_count) {row_max = row_count; irow_max = y+1;}
    }

    cout << irow_max << '\n';
}
