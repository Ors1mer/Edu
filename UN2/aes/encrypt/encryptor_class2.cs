using System;
using System.IO;
using System.Text;
using System.Linq;
using System.Security.Cryptography;

namespace EncryptorSpace {
    public static class Encryptor {
        // Sizes
        private const int BlockS = 128 / 8;
        private const int PasswordS = 256 / 8;
        // Used encoding
        private static readonly Encoding StrEncode = Encoding.UTF8;

        public static byte[] Encrypt(string data, string password) {
            var key = sha(password);
            var iv = random_bytes(BlockS);

            var enc_data = EncryptStringToBytes_Aes(data, key, iv);
            return concat(iv, enc_data);
        }

        public static string Decrypt(byte[] enc_vals, string password) {
            var key = sha(password);
            var iv = enc_vals.Take(BlockS).ToArray();
            var enc_data = enc_vals.Skip(BlockS).ToArray();

            var data = DecryptStringFromBytes_Aes(enc_data, key, iv);
            return data;
        }

        private static byte[] sha(string password) {
            var pass_b = StrEncode.GetBytes(password);

            using (var hash = SHA256Managed.Create()) {
                return hash.ComputeHash(pass_b);
            }
        }

        private static byte[] random_bytes(int size) {
            var random_b = new byte[size];
            RandomNumberGenerator.Fill(random_b);
            return random_b;
        }

        private static byte[] concat(params byte[][] arrays) {
            var merged = new byte[arrays.Sum(a => a.Length)];
            var merge_i = 0;

            for (int i = 0; i < arrays.GetLength(0); i++) {
                arrays[i].CopyTo(merged, merge_i);
                merge_i += arrays[i].Length;
            }

            return merged;
        }

        static byte[] EncryptStringToBytes_Aes(string plainText, byte[] Key, byte[] IV)
        {
            // Check arguments.
            if (plainText == null || plainText.Length <= 0)
                throw new ArgumentNullException("plainText");
            if (Key == null || Key.Length <= 0)
                throw new ArgumentNullException("Key");
            if (IV == null || IV.Length <= 0)
                throw new ArgumentNullException("IV");
            byte[] encrypted;

            // Create an Aes object
            // with the specified key and IV.
            using (Aes aesAlg = Aes.Create())
            {
                aesAlg.Key = Key;
                aesAlg.IV = IV;

                // Create an encryptor to perform the stream transform.
                ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);

                // Create the streams used for encryption.
                using (MemoryStream msEncrypt = new MemoryStream())
                {
                    using (CryptoStream csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                    {
                        using (StreamWriter swEncrypt = new StreamWriter(csEncrypt))
                        {
                            //Write all data to the stream.
                            swEncrypt.Write(plainText);
                        }
                        encrypted = msEncrypt.ToArray();
                    }
                }
            }
            // Return the encrypted bytes from the memory stream.
            return encrypted;
        }

        static string DecryptStringFromBytes_Aes(byte[] cipherText, byte[] Key, byte[] IV)
        {
            // Check arguments.
            if (cipherText == null || cipherText.Length <= 0)
                throw new ArgumentNullException("cipherText");
            if (Key == null || Key.Length <= 0)
                throw new ArgumentNullException("Key");
            if (IV == null || IV.Length <= 0)
                throw new ArgumentNullException("IV");

            // Declare the string used to hold
            // the decrypted text.
            string plaintext = null;

            // Create an Aes object
            // with the specified key and IV.
            using (Aes aesAlg = Aes.Create())
            {
                aesAlg.Key = Key;
                aesAlg.IV = IV;

                // Create a decryptor to perform the stream transform.
                ICryptoTransform decryptor = aesAlg.CreateDecryptor(aesAlg.Key, aesAlg.IV);

                // Create the streams used for decryption.
                using (MemoryStream msDecrypt = new MemoryStream(cipherText))
                {
                    using (CryptoStream csDecrypt = new CryptoStream(msDecrypt, decryptor, CryptoStreamMode.Read))
                    {
                        using (StreamReader srDecrypt = new StreamReader(csDecrypt))
                        {

                            // Read the decrypted bytes from the decrypting stream
                            // and place them in a string.
                            plaintext = srDecrypt.ReadToEnd();
                        }
                    }
                }
            }
            return plaintext;
        }
    }
}
