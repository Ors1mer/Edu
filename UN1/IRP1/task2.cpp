#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");


    long double a, b, integral = 0;
    long double x1, x2, y1, y2;

    ifstream input("input2.in");
    if (!input) cerr << "Файлу не існує!"; //foolproof
    input >> x1 >> y1;
    a = x1; //the starting point of the integral

    //calculation of the integral
    do {

        input >> x2 >> y2;
        integral += (x2-x1)*(y1+y2)/2;
        x1 = x2; y1 = y2;
        b = x1; //the ending point of the integral

    } while (!input.eof());

    //create the output file
    ofstream output("out2.txt");
    //make cout/output always print 8 digits after the point
    cout.setf(ios::fixed);
    cout.precision(8);
    output.setf(ios::fixed);
    output.precision(8);

    cout << "Інтервал інтегрування: ["  << a  << "; " << b << "]\n";
    cout << "Значення інтегралу: " << integral;
    output << "Інтервал інтегрування: ["  << a  << "; " << b << "]\n";
    output << "Значення інтегралу: " << integral;

    input.close(); output.close();
}

