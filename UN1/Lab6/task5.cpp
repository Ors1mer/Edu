#include <iostream>

int main()
{
    const int N = 5;
    int64_t arr[N] = {243, 81, 27, 9, 3};
    uint16_t count;
    // Output the array
    for (int i = 0; i < N; i++)
        std::cout << arr[i] << ' ';
    // Counting local mins
    for (int i = 1; i < N-1; i++) {
        if (arr[i-1] > arr[i] && arr[i] < arr[i+1])
            count++;
    }
    std::cout << "\nThe amount of local mins is " << count << '\n';
}
