#include <iostream>

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");
    
    //declaring variables
    int64_t n;
    long double a1 = 1.0, a2 = 2.0, ak;
    

    cout << "Введiть N: ";
    cin >> n;
    
    //foolproof
    if (n <= 1) throw invalid_argument("Невірні дані! N має бути > 1!");
    
    //calculating
    for (uint64_t i = 1; i <= n; i++) {
        if (i == 1) {
            cout << a1;

        } else if (i == 2) {
            cout << a2;

        } else {
            ak = (a1 + 2*a2)/3;
            cout << ak;
            a1 = a2; a2 = ak;

        }

        if (i != n) cout << ", ";
    }
    cout << '\n';
}
