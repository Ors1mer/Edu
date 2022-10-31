#include <iostream>

int main()
{
    using std::cout, std::cin;
    double a, b; 

    cout << "Enter A & B (A >= B): ";
    cin >> a >> b;
    if(a < b || a <= 0 || b <= 0) {
        throw std::invalid_argument("Wrong input! A must be >= B "
                                    "and both numbers are positive!");
    }
    // the cycle
    do {
        a -= b;
    } while(a >= b);
    
    cout << "The length of untaken line A equals " << a << '\n';
}
