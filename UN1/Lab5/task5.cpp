#include <iostream>

/*
short max(const char& a, const char& b) {
    return a > b ? a : b;
}

long max(const long& a, const long& b) {
    return a > b ? a : b;
}

double max(const double& a, const double& b) {
    return a > b ? a : b;
}
*/

short max(const short& a, short b = 1) {
    return a > b ? a : b;
}

template <typename num>
num max(const num& a, const num& b) {
    return a > b ? a : b;
}

int main()
{
    using std::cout, std::cin;
    cout << max(12, 6.28) << '\n';
}
