#include <iostream>

int main()
{
    using std::cout, std::cin;
    double P;        // percent
    uint64_t M;      // total max kilometers
    uint64_t K = 1;  // days
    double S = 10.0; // kilometers total

    cout << "Enter the percent of race increase and desirable distance: ";
    cin >> P >> M;
    if((P >= 50) || (P <= 0)) {
        throw std::invalid_argument("P must be between 0 and 50");
    }

    // the cycle
    while(S <= M) {
        S += S*P*0.01;
        K++;
    }
    cout << "Total mileage: " << S << "\nDays: " << K << '\n';
}
