using System;
using System.Collections.Generic;
using System.Linq;

class Numbers {
    static bool IsPrimary(int num) {
        for (int i = 2; i <= num/2; i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    static void Main() {
        // Initialization
        bool primary_list;
        int[] numbers = new int[] {2, 2, 3, 1, 5, 7, 5};
        int initial_size = numbers.Length;

        // Linq query
        // Filter: save only prime numbers
        numbers = numbers.Where(n => IsPrimary(n)).ToArray();

        // If length of array didn't change, all numbers are primary
        primary_list = (numbers.Length - initial_size) == 0;
        //Print the result
        Console.WriteLine(primary_list ?
                          "The list is primary" :
                          "The list is not primary");
    }
}
