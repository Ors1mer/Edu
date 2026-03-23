#include <iostream>
#include <set>
#include <algorithm>

int main() {
    using namespace std;

    // Task: compute the difference of two sets (A / B) using STL set datastructures

    // Sets declaration
    set<uint16_t> two_powers = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    set<uint16_t> four_powers = {1, 4, 16, 64, 256, 1024, 4096};
    set<uint16_t> diff;
    
    // Calculating difference
    set_difference(two_powers.begin(), two_powers.end(), 
                   four_powers.begin(), four_powers.end(),
                   inserter(diff, diff.end()));

    // Printing the diff set
    for (auto it = diff.begin(); it != diff.end(); it++) {
        cout << *it << '\t';
    }
}
