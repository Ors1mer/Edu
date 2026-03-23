#include <iostream>

using namespace std;

int main() {
    // input & output variables respectively
    short num, reversed;

    // ask for input
    cout << "Enter the number: ";
    cin >> num;
    
    // getting needed digits, multiplying and summing them
    reversed = (num%10)*100 + (num/10%10)*10 + num/100;

    // display the reversed number
    cout << "The reversed number is: " << reversed << '\n';
}
