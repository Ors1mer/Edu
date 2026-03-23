#include <iostream>

void print_arr(int arr[], size_t size) {
    using namespace std;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << '\t';
    }
    cout << '\n';
}

void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

void selection_sort(int arr[], size_t size) {
    int i, j, min_i;

    for (i = 0; i < size; i++) {
        min_i = i;
        for (j = i+1; j < size; j++) {
            if (arr[j] < arr[min_i]) min_i = j;
        }

        swap(arr[i], arr[min_i]);
    }
}

void insertion_sort(int arr[], size_t size) {
    int i, j, key;

    for (i = 1; i < size; i++ ) {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
   }
}

void bubble_sort(int arr[], size_t size) {
    int i, j;

    for (i = 0; i <= size-1; i++) {
        for (j = 0; j < size-1-i; j++) {
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

void quicksort(int arr[], size_t size) {
    
}

int main() {
    size_t size = 9;
    int arr[size] = {40, 94, 81, 74, 79, 70, 23, 65, 45};

    bubble_sort(arr, size);
    print_arr(arr, size);
}
