#include <iostream>

int main() {
    using std::cout, std::cin;

    const int N = 10;
    long double arr[N] = {214, 43, -54, 4.5, 69, 196, -144, 256, -128, 512};

    int64_t count = 0;
    long double P;

    // Input
    cout << "Enter the P number: ";
    cin >> P;
    
    // Outputing the numbers of arr, bigger then P
    // And counting them
    for (int i = 0; i < N; i++) {
        if (arr[i] > P) {
            cout << arr[i] << "\t";
            count++;
        }
    }

    cout << "\nThe amount of numbers bigger then P: " << count;
}
