#include <iostream>

int main()
{
    using namespace std;
    double K, P, T, temp;
    // Asking for the input
    cout << "Enter the K: ";
    cin >> K;
    cout << "Enter the P: ";
    cin >> P;
    cout << "Enter the T: ";
    cin >> T;
    // Changing values
    temp = T;
    T = P;
    P = K;
    K = temp;
    // Variables' output
    cout << "T, P, K: " << T << ", " << P << ", " << K << "\n";
}
