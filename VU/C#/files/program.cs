using System;
using System.IO;

namespace App {

    internal class Program {
        static void Main(string[] args) {
            string action;
            bool flag = true;

            FilesMaker f = new FilesMaker("junk/");
            while (flag) {
                Console.WriteLine("Choose action (1 - create, 2 - report, 3 - delete): ");
                action = Console.ReadLine();
                switch (action) {
                    case "1":
                        Console.WriteLine("Write amount of files to create: ");
                        f.create(Int16.Parse(Console.ReadLine()));
                        Console.WriteLine("Done");
                        break;
                    case "2":
                        Console.WriteLine("Write report's name: ");
                        f.report(Console.ReadLine());
                        Console.WriteLine("Done");
                        break;
                    case "3":
                        Console.WriteLine("Deleting files that contain zero...");
                        f.delete();
                        Console.WriteLine("Done");
                        break;
                    default:
                        flag = false;
                        Console.WriteLine("Exiting the program...");
                        break;
                }
            }
        }
    }
}
