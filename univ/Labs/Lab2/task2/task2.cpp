#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "UA");
    // input values
    double x, y;
    // output value
    bool ans;
    cout << "Введіть координати точки у 2D:\n";
    cin >> x >> y;

    if ((x >= 0 && (pow(x, 2) + pow(y, 2)) <= 64) || 
        (x < 0  && (pow(x ,2) + pow(y, 2)) <= 16))
        ans = true;
    else
        ans = false;
    
    cout << "Чи знаходиться точка у області? " << boolalpha << ans << '\n';

}
