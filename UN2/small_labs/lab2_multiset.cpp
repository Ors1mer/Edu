#include <iostream>
#include <set>
#include <algorithm>

int main() {
    using namespace std;

    // Task: compute the union (A U B) of two sets using STL MULTISET datastructures

    // Declaring multisets
    multiset<uint16_t> A = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    multiset<uint16_t> B = {0, 1, 3, 6, 2, 7, 13, 20, 12, 21};
    multiset<uint16_t> C;

    // Calculating the union
    set_union(A.begin(), A.end(),
              B.begin(), B.end(), 
              inserter(C, C.end()));

    // Printing the C multiset
    for (auto it = C.begin(); it != C.end(); it++) {
        cout << *it << '\t';
    }
}
