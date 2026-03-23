using System;
using System.IO;
using System.Linq;
using System.Threading;
using EncryptorSpace;

class ProgramCLI {
    // These values used to make the charset
    static string alphalow = "abcdefghijklmnopqrstuvwxyz";
    static string alphaup = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static string num = "0123456789";
    static string symbol = "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~";
    // Consts
    private  const string no_success = "__not_foundXAEA@!";

    static void Main(string[] args) {
        string EFile;
        string Charset;
        int Nthreads, Length;
        (EFile, Nthreads, Length, Charset) = ParseArgs(args);
        Console.WriteLine("Brute-force started\n");
        Hack(EFile, Charset, Nthreads, Length);
    }

    //
    // --- Password guess functions ---
    //

    static void Hack(string Fname, string Charset,
                         int Nthreads, int Length) {
        // Open the encrypted file
        byte[] data = File.ReadAllBytes(Fname);

        // Brute-force
        string plaintext = BruteForce(data, Charset, Nthreads, Length);

        // Write decrypted data to file
        if (plaintext != no_success)
            Console.WriteLine($"Hacked! Decrypted data:\n{plaintext}");
            //File.WriteAllBytes(fname, crypt_data);
        else
            Console.WriteLine("Couldn't find the right password!");
    }

    static string BruteForce(byte[] data, string Charset, int N, int L) {
        string plaintext = no_success;

        for (int l = 1; (l <= L) && (plaintext == no_success); l++) {
            char[] start = Fill(Charset[0], l);
            char[] end_comb = Fill(Charset[Charset.Length-1], l);
            plaintext = combinator(start, end_comb, Charset, data);
        }

        return plaintext;
    }

    private static string combinator(char[] start, char[] end,
                                     string Charset,
                                     byte[] data) {
        var comb = start;
        while (true) {
            ReWrite(comb);

            var pass_str = string.Join("", comb);
            try {
                string plaintext = Encryptor.Decrypt(data, pass_str);
                return plaintext;
            } catch {}

            if (Enumerable.SequenceEqual(comb, end))
                return no_success;
            comb = next_comb(comb, Charset);
        }
    }

    private static char[] next_comb(char[] arr, string Charset) {
        for (int i = arr.Length - 1; i >= 0; i--) {
            if (arr[i] == Charset[Charset.Length - 1]) {
                arr[i] = Charset[0];
                continue;
            }
            var chars = Charset.ToCharArray();
            int char_indx = Array.IndexOf(chars, arr[i]);
            arr[i] = chars[char_indx+1];
            break;
        }
        return arr;
    }

    private static void ReWrite(char[] text) {
        Console.SetCursorPosition(0, Console.CursorTop-1);
        Console.Write(new String(' ', Console.BufferWidth));
        Console.SetCursorPosition(0, Console.CursorTop-1);
        Console.WriteLine(string.Join("", text));
    }

    private static char[] Fill(char filler, int l) {
        var arr = new char[l];
        for (int i = 0; i < l; i++)
            arr[i] = filler;
        return arr;
    }

    //
    // --- Arguments parsing ---
    //

    static (string, int, int, string) ParseArgs(string[] args) {
        string EFile;
        int Nthreads, Length;
        string Charset;
        string help_msg = "Usage:\n" +
                   "hack file [-c threads_number] " +
                   "[-l max_password_length] [-s charsets...]\n" +
                   "Possible charsets: alphalow, alphaup, num, symbol\n";

        if (args.Length == 0 || !File.Exists(args[0])) {
            Console.WriteLine(help_msg);
            ErrExit();
        } else
            EFile = args[0];

        Nthreads = ArgValue("-c", args, 1);
        Length = ArgValue("-l", args, 128);
        Charset = GetCharset("-s", args, "alphalowalphaupnumsymbol");

        return (EFile, Nthreads, Length, Charset);
    }

    private static void ErrExit() {
        Environment.Exit(1);
    }

    private static int ArgValue(string arg, string[] args, int def) {
        var argvar = def;
        var i = Array.IndexOf(args, arg);
        if (args.Contains(arg))
            argvar = Int16.Parse(args[i+1]);
        return argvar;
    }

    private static string GetCharset(string arg, string[] args, string def) {
        var argvar = def;
        var i = Array.IndexOf(args, arg);

        if (args.Contains(arg)) {
            argvar = "";
            for (int j = i+1; j < args.Length; j++)
                argvar += args[j];
        }

        argvar = argvar.Replace("alphalow", alphalow);
        argvar = argvar.Replace("alphaup", alphaup);
        argvar = argvar.Replace("num", num);
        argvar = argvar.Replace("symbol", symbol);

        return argvar;
    }
}
