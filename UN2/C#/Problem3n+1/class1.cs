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
}
