#include <iostream>

int main()
{
    using std::cout, std::cin;
    double a;
    double k = 2;
    double r = 0.5; // summing result
    
    cout << "Enter А: ";
    cin >> a;
    if(a <= 1) {
        throw std::invalid_argument("А must be greater than 1");
    }

    // The cycle
    while((r + (k/(k+1))) < a) {
        r += k/(k+1);
        k++;
    }
    cout << "K = " << --k << "\nThe sum = " << r << '\n';
}
