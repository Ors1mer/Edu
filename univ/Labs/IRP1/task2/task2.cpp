#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");
    
    long double integral_value = 0;
    int64_t lines = -1;

    //get the amount of lines in the file
    ifstream input("input.in");
    if (!input) cerr << "Файлу не існує!";
    string s;
    while (!input.eof()) {
        getline(input, s);
        lines++;
    }
    input.clear();
    input.seekg(0, ios::beg);
    
    //array, which shall store all point values from the file
    long double points[lines][2];
    for (int l = 0; l < lines; l++) {
        input >> points[l][0] >> points[l][1];
    }


    //calculation of the integral
    long double x, y;
    for (int i = 0; i < lines-1; i++) {
        x = points[i+1][0] - points[i][0];
        y = (points[i][1] + points[i+1][1])/2;
        integral_value += x*y;
    }
   
    //create the output file
    ofstream output("outKaunin.txt");
    //make cout/output always print 8 digits after the point
    cout.setf(ios::fixed);
    cout.precision(8);
    output.setf(ios::fixed);
    output.precision(8);

    cout << "Інтервал інтегрування: ["  << points[0][0]  << "; " << points[lines-1][0] << "]\n";
    cout << "Значення інтегралу: " << integral_value;
    output << "Інтервал інтегрування: ["  << points[0][0]  << "; " << points[lines-1][0] << "]\n";
    output << "Значення інтегралу: " << integral_value;

    input.close(); output.close();
}
