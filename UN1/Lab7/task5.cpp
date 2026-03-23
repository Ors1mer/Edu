#include <iostream>

int main()
{
    using std::cout, std::cin;
    size_t M = 4, N = 3;
    int64_t matrix[M][N] = {{-3, 2, -4},
                             {4, -4, 4},
                             {-5, -5, -3},
                             {4, 3, 1}};

    for(int y = 0; y < M; y++) {
        for(int x = 0; x < N; x++) {
            cout << matrix[y][x] << '\t';
        }
        cout << '\n';
    }
    cout << '\n';

    bool found = false;
    int index = 0;
    uint64_t pos, neg;
    for(int x = 0; x < N && !found; x++) {
        pos = 0;
        neg = 0;
        for(int y = 0; y < M; y++) {
             if(matrix[y][x] > 0)
                 pos++;
             else if(matrix[y][x] < 0)
                 neg++;
        }
        if(pos == neg) {
            found = true;
            index = x+1;
        }
    }
    cout << index << '\n';
}
