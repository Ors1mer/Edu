#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");
    
    long double integral = 0, a, b;
    long double x1, y1, x2, y2;

    //open input file
    ifstream input("input.in");
    //initial reading is needed to define a
    input >> x1 >> y1 >> x2 >> y2;
    a = x1;
    
    //calculating integral
    do {
        integral += (x2-x1)*(y1+y2)/2;

        x1 = x2; y1 = y2;
        input >> x2 >> y2;
        b = x2;

    } while (!input.eof());

    //create the output file
    ofstream output("outKaunin.txt");
    //make cout/output always print 8 digits after the point
    cout.setf(ios::fixed);
    cout.precision(8);
    output.setf(ios::fixed);
    output.precision(8);

    cout << "Інтервал інтегрування: ["  << a << "; " << b << "]\n";
    cout << "Значення інтегралу: " << integral;
    output << "Інтервал інтегрування: [" << a  << "; " << b << "]\n";
    output << "Значення інтегралу: " << integral;
}
