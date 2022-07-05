#include <iostream>
#include <iterator>
#include <list>

bool IsPrimary(uint64_t a) {
    for (int i = 2; i <= a/2; i++) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    using namespace std;

    //Initialization
    bool primary_list = true;
    list<int> numbers({2, 43, 2, 3, 1, 5, 7, 5});
    
    for (int el:numbers) {
        cout << el << '\t';
        if (!IsPrimary(el)) {
            primary_list = false;
            break;
        }
    }

    cout << '\n' << primary_list << '\n';
}
