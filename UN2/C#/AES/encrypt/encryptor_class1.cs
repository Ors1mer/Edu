using System;
using System.Text;
using System.Linq;
using System.Security.Cryptography;

namespace EncryptorSpace {
    public static class Encryptor {
        // Sizes
        private const int BlockS = 128 / 8;
        private const int SaltS = 128 / 8;
        private const int PasswordS = 256 / 8;
        private const int SignS = 256 / 8;
        private const int IterC = 1000;
        // Used encoding
        private static readonly Encoding StrEncode = Encoding.UTF8;

        public static byte[] Encrypt(string data, string password) {
            using (var aes = Aes.Create()) {
                var salt = random_bytes(SaltS);
                var key = saltify(password, salt);
                var iv = random_bytes(BlockS);

                var data_b = StrEncode.GetBytes(data);
                var signed_data = concat(sha256(data), data_b);

                using (var encryptor = aes.CreateEncryptor(key, iv)) {
                    var crypt_data = encryptor
                                     .TransformFinalBlock(signed_data,
                                                0, signed_data.Length);
    
                    return concat(salt, iv, crypt_data);
                }
            }
        }
    
        public static string Decrypt(byte[] enc_vals, string password) {
            using (var aes = Aes.Create()) {
                var salt = enc_vals.Take(SaltS).ToArray();
                var key = saltify(password, salt);
                var iv = enc_vals.Skip(SaltS).Take(BlockS).ToArray();
                var enc_data = enc_vals.Skip(SaltS + BlockS).ToArray();
    
                using (var encryptor = aes.CreateDecryptor(key, iv)) {
                    var s_data = encryptor
                        .TransformFinalBlock(enc_data, 0, enc_data.Length);

                    // Check data signature
                    var sign = s_data.Take(SignS).ToArray();
                    var data = s_data.Skip(SignS).ToArray();
                    string pure_data = StrEncode.GetString(data);
                    if (!Enumerable.SequenceEqual(sign, sha256(pure_data)))
                        throw new System.ArgumentException("password");

                    return pure_data;
                }
            }
        }
    
        private static byte[] saltify(string password, byte[] salt) {
            var pass_b = StrEncode.GetBytes(password);
    
            using (var derivator = new Rfc2898DeriveBytes(
                   pass_b, salt, IterC, HashAlgorithmName.SHA256))
            {
                return derivator.GetBytes(PasswordS);
            }
        }

        private static byte[] sha256(string text) {
            var text_b = StrEncode.GetBytes(text);

            using (var hash = SHA256Managed.Create()) {
                return hash.ComputeHash(text_b);
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
    }
}
