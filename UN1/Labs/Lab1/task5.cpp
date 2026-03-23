#include <iostream>

using namespace std;

int main() {
    // input variable
    unsigned long size;
    // output variables
    unsigned long KB, MB, B;

    // ask for input
    cout << "Enter the file size: ";
    cin >> size;
    
    // calculations
    // (1<<20) == 1024^2
    MB = size/(1<<20);
    KB = (size%(1<<20))/1024;
    B = size%1024;
    
    // output
    cout.setf(ios::fixed);
    cout.precision(5);
    cout << "Megabytes: " <<  MB << endl
         << "Kilobytes: " <<  KB << endl
         << "Bytes:     " <<  B << endl;
}
