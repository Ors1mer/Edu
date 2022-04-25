using System;
using System.Collections.Generic;
using System.Linq;

namespace App {

    class Problem3n1 {
        private List<int> seq = new List<int>();

        public List<int> sequence(int num) {
            seq.Clear();

            while (num > 1) {
                if (num % 2 == 1)
                    num = 3*num + 1;
                else
                    num /= 2;
                seq.Add(num);
            }

            return seq;
        }

        public void print_sequence() { // Function with a side effect
            Console.Write("Sequence:");
            foreach (int num in seq)
                Console.Write(" " + num);
            Console.WriteLine();
        }

        public long count() {
            return seq.Count;
        }

        public long max() {
            if (seq.Count > 0)
                return seq.Max();
            return 1;
        }
        
        public struct Solution {
            public long num;
            public long count;
            public long max;
        }

        public List<Solution> range(int start, int end) {
            List<Solution> result = new List<Solution>();
            Solution nsolution;
            
            for (int num = start; num <= end; num++) {
                this.sequence(num);

                nsolution.num = num;
                nsolution.count = this.count();
                nsolution.max = this.max();

                result.Add(nsolution);
            }

            return result;
        }

        public Solution min_iterations(List<Solution> solutions) {
            long min = Int32.MaxValue;
            Solution result = new Solution();
            foreach (Solution sol in solutions) {
                if (sol.count < min) {
                    min = sol.count;
                    result = sol;
                }
            }
            return result;
        }

        public Solution max_iterations(List<Solution> solutions) {
            long max = 0;
            Solution result = new Solution();
            foreach (Solution sol in solutions) {
                if (sol.count > max) {
                    max = sol.count;
                    result = sol;
                }
            }
            return result;
        }
    }

    internal class Program {
        static void Main(string[] args) {
            // Variable declaration
            string input, start_i, end_i;
            int num = 0;
            int start = 0, end = 0;
            List<Problem3n1.Solution> solutions = new List<Problem3n1.Solution>();
            Problem3n1.Solution extremum_solution;
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

            // --- Task 3: find min and max iteration numbers ---
            Console.WriteLine("\nSolution with minimum iterations: ");
            extremum_solution = task.min_iterations(solutions);
            Console.WriteLine("Number: " + extremum_solution.num + "\nCount: " + extremum_solution.count + "\nMax: " + extremum_solution.max);

            Console.WriteLine("Solution with maximum iterations: ");
            extremum_solution = task.max_iterations(solutions);
            Console.WriteLine("Number: " + extremum_solution.num + "\nCount: " + extremum_solution.count + "\nMax: " + extremum_solution.max);

            Console.WriteLine("\nThat's all, folks!"); 
        }
    }
}
