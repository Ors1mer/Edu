#include <iostream>


int main() {
    using namespace std;
    // input & output values
    unsigned short d, m;

    cout << "Enter the month and the day: ";
    cin >> d >> m;

    if (d == 1) {
        --m;
        switch (m) {
            case 1: case 2: case 4: case 6: case 8: case 9: case 11:
                d = 31;
                break;
            case 5: case 7: case 10: case 12:
                d = 30;
                break;
            case 3:
                d = 28;
                break;
        }}
    else --d;

    cout << "The previous date is: " << d << '.' << m << '\n';
}
