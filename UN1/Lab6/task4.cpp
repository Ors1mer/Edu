#include <iostream>

int main() {
    using std::cout;

    // Initializing the array
    const int N = 5;
    int64_t arr[N] = {243, 81, 27, 9, 3};

    // Print the array
    for (int i = 0; i < N; i++) {
        cout << arr[i] << ' ';
    }

    bool check = true;
    // Check for declining sequence
    for (int i = 0; i < N-1 && check; i++) {
        if (arr[i] < arr[i+1]) {
            cout << "\nThe answer is: " << i+1 << '\n';
            check = false;
        }
    }

    if (check) cout << "\nThe answer is: " << 1 << '\n';
}
