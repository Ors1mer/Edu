#include <iostream>
#include <cstring>
#include <fstream>

using namespace std; // I didn't wanna do this

bool reverse_C(char s1[], char s2[])
{
    bool ans = true;

    // If rows have different length, they can't be reverse
    // of each other
    if (strlen(s1) != strlen(s2)) ans = false;

    size_t length = strlen(s1)-1;
    for (int i = 0; i < length && ans; i++) {
        if (s1[i] != s2[length-i]) ans = false;
    }

    return ans;
}

bool reverse_Cpp(string s1, string s2)
{
    bool ans = true;

    if (s1.length() != s2.length()) ans = false;

    size_t length = s1.length()-1;
    for (int i = 0; i < length && ans; i++) {
        if (s1[i] != s2[length-i]) ans = false;
    }

    return ans;
}

int main()
{
    // Declaring variables
    const size_t T = 4;
    // C style
    char s1[256];
    char c[2];
    char words[30][20];   // max 30 words with length <= 20
    char words_rp[T][20]; // words with reversed pairs
    int words_count = 0;
    // C++ style
    string s2;
    // Open the file
    ifstream fin("input.txt");
    // Write into s1
    while(fin) {
        fin.get(c[0]);
        strcat(s1, c);
    }
    s1[strlen(s1)-1] = '\0'; // append NULL
    // Write into s2
    // Move to beginning of the file
    fin.clear();
    fin.seekg(0);
    getline(fin, s2); // write to s2
    s2.append("\0");
    // Create array of words
    char *tk;
    char dim[] = ", .!?";
    int i = 0;
    tk = strtok(s1, dim);

    while(tk != NULL) {
        for (int j = 0; j < strlen(tk); j++) {
            words[i][j] = *(tk + j);
        }
        words_count++;

        tk = strtok(NULL, dim);
        i++;
    }
    // Write all words that have reversed pairs into words_rp
    int t = 0;
    for (int i = 0; i < words_count; i++) {
        for (int j = i+1; j < words_count; j++) {
            if (reverse_C(words[i], words[j])) {
                cout << words[i] << '\t';
                strcpy(words_rp[t], words[i]);
                t++;
                break;
            }
        }
    }
    // Sort array words_rp alphabeticaly
    // Bubble sort
    /*
     * not implemented
     */
}
