#include <iostream>

using namespace std;

int main() {
    // input & output variables
    double K, P, T;
    // temporary variables for storing values
    double temp;

    // asking for the input
    cout << "Enter the K: ";
    cin >> K;
    cout << "Enter the P: ";
    cin >> P;
    cout << "Enter the T: ";
    cin >> T;

    // changing values
    temp = T;
    T = P;
    P = K;
    K = temp;

    // variables' output
    cout << "T, P, K: " << T << ", " << P << ", " << K << "\n";
}
