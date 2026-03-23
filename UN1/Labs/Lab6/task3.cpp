#include <iostream>
#include <fstream>

int main() {
    using namespace std;

    const int N = 7; // Must be an odd number
    long double arr[N] = {};

    // Getting the file stream
    ifstream fin("input.in");
    if (!fin) cerr << "Файл порожній або не існує";

    // Reading data from the file
    for (int i = 0; i < N; i++) {
        fin >> arr[i];
    }

    // Output for last to first, odd indexes only
    for (int i = N - 1; i >= 0; i -= 2) {
        cout << arr[i] << '\t';
    }
    cout << '\n';
}
