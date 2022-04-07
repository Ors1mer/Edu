using System;

namespace MyApp {
    internal class Program {
        static void Main(string[] args) {
            Console.WriteLine(args[0]);
        }
    }

}
// To compile: mcs -out:hello hello.cs
