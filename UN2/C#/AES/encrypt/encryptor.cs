using System;
using System.IO;
using System.Text;
using System.Security.Cryptography;
using System.Collections.Generic;
using EncryptorSpace;

class ProgramCLI {
    static void Main(string[] args) {
        // Declarations
        ParsedArgs param = ArgParse(args);

        foreach (var fname in param.files) {
            if (param.action == task.encrypt) {
                string data = File.ReadAllText(fname);
                var crypt_data = Encryptor.Encrypt(data, param.password);
                File.WriteAllBytes(fname, crypt_data);
            } else {
                byte[] data = File.ReadAllBytes(fname);
                string plain_data = Encryptor.Decrypt(data, param.password);
                File.WriteAllText(fname, plain_data);
            }
        }
    }

    private enum task {encrypt, decrypt}
    private struct ParsedArgs {
        public task action;
        public string password;
        public List<string> files;
    }

    private static bool IsActionArg(string arg) {
        return (arg == "-d" || arg == "--decrypt");
    }

    private static void HandleWrongInput(string[] args) {
        string help_msg = "Usage:\nencryptor [-d] filenames... password";
        string[] small_amount_err = {
            "You didn't provide any arguments!",
            "You didn't provide file(s) and/or password",
        };
        // Checks if enough amount of arguments is given
        if (args.Length < 2) {
            Console.WriteLine(small_amount_err[args.Length]);
            Console.WriteLine(help_msg);
            Environment.Exit(1);
        }
    }

    static ParsedArgs ArgParse(string[] args) {
        ParsedArgs parameters;

        // Wrong input check, in this case finish program
        HandleWrongInput(args);
        // Filling up the parameters
        parameters.password = args[args.Length-1];
        List<string> filepaths = new List<string>(args);
        filepaths.RemoveAt(args.Length-1);
        if (IsActionArg(args[0])) {
            parameters.action = task.decrypt;
            filepaths.RemoveAt(0);
        } else {
            parameters.action = task.encrypt;
        }
        parameters.files = filepaths;
        return parameters;
    }

    static string ByteToStr(byte[] data) {
        return Encoding.UTF8.GetString(data);
    }

    static byte[] StrToByte(string data) {
        return Encoding.UTF8.GetBytes(data);
    }
}
