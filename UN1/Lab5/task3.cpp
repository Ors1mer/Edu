#include <iostream>

//reference solution
void digitCountSum(uint64_t k, uint16_t &c, uint16_t &s)
{
    c = 0, s = 0;
    while(k) {
        c++;
        s += k%10;
        k /= 10;
    }
}

//pointers solution
void digitCountSum(uint64_t k, uint16_t* c, uint16_t* s)
{
    *c = 0, *s = 0;
    while(k) {
        (*c)++;
        *s += k%10;
        k /= 10;
    }
}


int main()
{
    using namespace std;
    cout << "Enter 5 numbers: ";
    uint64_t nums[5];
    for (short i = 0; i <= 4; i++) cin >> nums[i];
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
    }
}
