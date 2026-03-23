#include <iostream>

<<<<<<< HEAD
uint64_t* digitCountSum(uint64_t k) {
    uint64_t C = 0, S = 0;
=======
//reference solution
void digitCountSum(uint64_t k, uint16_t &c, uint16_t &s) {
    c = 0, s = 0;
>>>>>>> 821a242 (Lab5: Completely finished tasks 3 & 4, partially completed task 5)
    while (k) {
        S += k%10;
        C++;
        k /= 10;
    }
    static uint64_t arr[2] = {C, S};
    return arr;
}

//pointers solution
void digitCountSum(uint64_t k, uint16_t* c, uint16_t* s) {
    *c = 0, *s = 0;
    while (k) {
        (*c)++;
        *s += k%10;
        k /= 10;
    }
}


int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");

    cout << "Введiть 5 чисел: ";
    uint64_t nums[5];
    uint64_t* CS;
    for (uint16_t i = 0; i <= 4; i++) cin >> nums[i];

<<<<<<< HEAD
    for (uint16_t i = 0; i <= 4; i++) {
        CS = digitCountSum(nums[i]);
        cout << "Кiлькicть цифр: " << CS[0] << ", сума цифр: " << CS[1] << '\n';
=======
    //getting answers c and s for every num from nums
    //using two distinct functions
    uint16_t c, s;
    uint16_t* c_ptr = &c, *s_ptr = &s; //declaring pointers
    cout << "Reference" << "\t" << "Pointer" << '\n';
    for (short i = 0; i <= 4; i++) {
        digitCountSum(nums[i], c, s);
        cout << c << '\t'  << s << '\t';
        
        digitCountSum(nums[i], &c, &s);
        cout << c << '\t' << s << '\n';
>>>>>>> 821a242 (Lab5: Completely finished tasks 3 & 4, partially completed task 5)
    }
}
