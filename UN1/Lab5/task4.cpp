#include <iostream>

//swap is used in sorting functions
void swap(long double &a, long double &b) {
    long double t = a;
    a = b; b = t;
}

//references solution
void sortInc3(long double &a, long double &b, long double &c) {
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
}

//pointers solution
void sortInc3(long double* a, long double* b, long double* c) {
    if (*a > *b) swap(*a, *b);
    if (*a > *c) swap(*a, *c);
    if (*b > *c) swap(*b, *c);
}

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");

    //declaring arrays
    long double arr1[3], arr2[3];
    //declaring pointers
    long double* a, *b, *c;

    cout << "Введiть три числа: ";
    cin >> arr1[0] >> arr1[1] >> arr1[2];
    cout << "Введiть iншi три числа: ";
    cin >> arr2[0] >> arr2[1] >> arr2[2];

    sortInc3(&arr1[0], &arr1[1], &arr1[2]);
    for (short i = 0; i <= 2; i++) cout << arr1[i] << '\t';
    cout << '\n';

    sortInc3(arr2[0], arr2[1], arr2[2]);
    for (short i = 0; i <= 2; i++) cout << arr2[i] << '\t';
}
