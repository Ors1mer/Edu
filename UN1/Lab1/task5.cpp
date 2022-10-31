#include <iostream>

int main()
{
    using namespace std;
    unsigned long KB, MB, B, size;

    cout << "Enter the file size: ";
    cin >> size;
    // Calculations
    // (1<<20) == 1024^2
    MB = size/(1<<20);
    KB = (size%(1<<20))/1024;
    B = size%1024;
    // Output
    cout.setf(ios::fixed);
    cout.precision(5);
    cout << "Megabytes: " <<  MB << endl
         << "Kilobytes: " <<  KB << endl
         << "Bytes:     " <<  B << endl;
}
