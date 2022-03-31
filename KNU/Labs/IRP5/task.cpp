#include <iostream>
#include <cstring>

using namespace std;

// Task 1
void remove_C(char s1[], char s2[]) {
    char* p = strstr(s1, s2);

    if (p) {
        strcpy(p, p+strlen(s2));
        printf("%s\n", s1);
    } else {
        printf("Substring not found!\n");
    }
}

void remove_Cpp(string& s1, string& s2) {
    size_t start = s1.find(s2); // the first index of substring

    if (start != string::npos) {
        s1.erase(start, s2.length());
        cout << s1 << '\n';
    } else {
        cout << "Substring not found!\n";
    } 
}

// Task 2
void insertion_C(char s1[], char s2[], char c[]) {
    char* p = strstr(s1, c);
    char s3[128] = "\0"; // additional string for storing the tail

    if (p && ((strlen(s1) + strlen(s2)) < 128)) {
        p += 1;             // moving to one index right
        strcpy(s3, p);      // save the tail 
        strcpy(p, s2);      // paste s2 instead of the tail
        p = p + strlen(s2); // move pointer to the end of the string
        strcpy(p, s3);      // append the tail
        cout << s1 << '\n';
//        printf("%s\n", s1);
        
    } else {
        printf("Character not found!\n");
    }
}

void insertion_Cpp(string& s1, string& s2, string& c) {
    size_t start = s1.find(c);

    if (start != string::npos) {
        s1.insert(start+1, s2);
        cout << s1 << '\n';
    } else {
        cout << "Character not found!\n";
    }
}

// Task 3
void copy_C(char s[], char x[]) {
    char* p = s + 3; // setting the pointer to 4th position

    if (p && strlen(s) >= 6) {
        strncpy(x, p, 3);    // copypaste 3 symbols into x
        x[strlen(x)] = '\0'; // append NULL symbol
        printf("%s\n", x);
    } else {
        printf("The string is too short!\n");
    }
}

void copy_Cpp(string& s, string& x) {
    if (s.length() >= 6) {
       x = s.substr(3, 3); 
       cout << x << '\n';
    } else {
       cout << "The string is too short!\n"; 
    }
}

// Task 4
void delete_C(char s[], char c1[], char c2[]) {

}

void delete_Cpp(string s, string c1, string c2) {

}

int main() {
    // Declaring variables
    // C style
    char s1[] = "123456 w typeertyu read mff";
    char to_remove1[] = "type";
    char to_paste1[] = "hile";
    char c1[] = "w";
    char x1[4];
    char letter1[] = "m", letter2[] = "f";
    // C++ style
    string s2 = "123456 w typeertyu read mff";
    string to_remove2 = "type";
    string to_paste2 = "hile";
    string c2 = "w";
    string x2;
    char letter3 = 'm', letter4 = 'f';
    

    cout << "Task 1\n";
    remove_C(s1, to_remove1); 
    remove_Cpp(s2, to_remove2);

    cout << "\nTask 2\n";
    insertion_C(s1, to_paste1, c1);
    insertion_Cpp(s2, to_paste2, c2);

    cout << "\nTask 3\n";
    copy_C(s1, x1);
    copy_Cpp(s2, x2);

    cout << "\nTask 4\n";
    delete_C(s1, letter1, letter2);
//    delete_Cpp(s2, letter3, letter4);
}
