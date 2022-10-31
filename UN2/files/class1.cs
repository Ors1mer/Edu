using System;
using System.IO;
using System.Text.RegularExpressions;

namespace App {

    public interface FileManager {
        void create(int amount);
        void report(string report_name);
        void delete();
    }

    public class FilesMaker : FileManager {
        private string dir;

        public FilesMaker(string path) => dir = path;

        public void create(int amount) {
            string name, new_name;
            string date;
            Random rnd = new Random();

            for (int n = 1; n <= amount; n++) {
                name = dir + "file" + n.ToString() + ".txt";
                date = DateTime.UtcNow.ToString("MM-dd-yyyy-HH:mm:ss");
                if (File.Exists(name)) {
                    // rename
                    new_name = dir + "file" + n.ToString() + "_" + date + ".txt";
                    File.Move(name, new_name);
                }
                File.WriteAllText(name, rnd.Next(0, 2).ToString());
            }
        }

        private FileInfo[] list_directory_files() {
            // creates an array of fileinfos which are stored in dir
            DirectoryInfo location = new DirectoryInfo(dir);
            FileInfo[] files = location.GetFiles();
            return files;
        }

        public void report(string report_name) {
            int val, ones = 0, zeros = 0;
            // get the info about files from dir
            FileInfo[] files = list_directory_files();
            Regex regex = new Regex("file[0-9]+.txt");
            // read data from each file and count ones and zeros
            foreach (FileInfo file in files) {
                if (regex.IsMatch(file.Name)) {
                    val = Int16.Parse(File.ReadAllText(dir + file.Name));
                    if (val == 1)
                        ones++;
                    else
                        zeros++;
                }
            }
            // write report
            string message = "Ones in the files: " + ones.ToString() + "\nZeros in the files: " + zeros.ToString();
            File.WriteAllText(dir + report_name, message);
        }

        public void delete() {
            // deletes all of the files that contain 0
            string val;
            FileInfo[] files = list_directory_files();
            
            foreach (FileInfo file in files) {
                val = File.ReadAllText(dir + file.Name);
                if (val == "0")
                    File.Delete(dir + file.Name);
            }
        }
    }
}
