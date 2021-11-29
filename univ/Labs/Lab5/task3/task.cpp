#include <iostream>

uint64_t* digitCountSum(uint64_t k) {
    uint64_t C = 0, S = 0;
    while (k) {
        S += k%10;
        C++;
        k /= 10;
    }
    static uint64_t arr[2] = {C, S};
    return arr;
}

int main() {
    using namespace std;
    setlocale(LC_CTYPE, "UA");

    cout << "Введiть 5 чисел: ";
    uint64_t nums[5];
    uint64_t* CS;
    for (uint16_t i = 0; i <= 4; i++) cin >> nums[i];

    for (uint16_t i = 0; i <= 4; i++) {
        CS = digitCountSum(nums[i]);
        cout << "Кiлькicть цифр: " << CS[0] << ", сума цифр: " << CS[1] << '\n';
    }
}
