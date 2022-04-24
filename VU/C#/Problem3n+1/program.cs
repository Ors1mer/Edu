using System;
using System.Collections.Generic;
using System.Linq;

namespace App {

    internal class Program {
        static void Main(string[] args) {
            // Variable declaration
            string input, start_i, end_i;
            int num = 0;
            int start = 0, end = 0;
            List<Problem3n1.Solution> solutions = new List<Problem3n1.Solution>();
            Problem3n1 task = new Problem3n1();
            
            // --- Task 1: output solution for exact number ---
            // Input processing
            Console.Write("Enter a natural number: ");
            input = Console.ReadLine();
            try {
                num = Int32.Parse(input);
                if (num <= 0)
                    throw new FormatException();
            } catch (FormatException) {
                Console.WriteLine("Invalid input! A positive integer is required!");
            }
            // Create sequence
            task.sequence(num);
            // Print the values: sequence, count, max
            task.print_sequence();
            Console.WriteLine("Count:\t\t" + task.count());
            Console.WriteLine("Max:\t\t" + task.max());

            // --- Task 2: solve sequences for the range of numbers ---
            // Input processing
            Console.WriteLine("\nEnter the range (the start and the end, natural numbers): ");
            start_i = Console.ReadLine();
            end_i = Console.ReadLine();
            try {
                 start = Int32.Parse(start_i);
                 end = Int32.Parse(end_i);
                 if (start <= 0 || end <= 0 || start >= end)
                    throw new FormatException();
            } catch (FormatException) {
                Console.WriteLine("Invalid input! Positive integers are required!");
            }
            // Do solutions
            solutions = task.range(start, end);
            // Print the table
            Console.WriteLine("Number\tCount\tMax");
            foreach (Problem3n1.Solution sol in solutions) {
                Console.WriteLine(sol.num + "\t" + sol.count + "\t" + sol.max);
            }

            Console.WriteLine("\nThat's all, folks!"); 
        }
    }
}
