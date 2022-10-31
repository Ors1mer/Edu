#include <iostream>
#include <cmath>

int main()
{
    using namespace std;
    double x, y;
    bool ans;

    cout << "Enter the 2D coordinates:\n";
    cin >> x >> y;

    if ((x >= 0 && (pow(x, 2) + pow(y, 2)) <= 64) || 
        (x < 0  && (pow(x ,2) + pow(y, 2)) <= 16))
        ans = true;
    else
        ans = false;
    
    cout << "Is point's location in the area? " << boolalpha << ans << '\n';
}
