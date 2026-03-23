#include <iostream>
#include <cstring>

using namespace std; // I didn't wanna do this

// Task 1
void remove_C(char s1[])
{
    char s2[] = "type";
    char* p = strstr(s1, s2);

    if(p) {
        strcpy(p, p+strlen(s2));
        printf("%s\n", s1);
    } else {
        printf("Substring not found!\n");
    }
}

void remove_Cpp(string& s1)
{
    string s2 = "type";
    size_t start = s1.find(s2); // the first index of substring

    if(start != string::npos) {
        s1.erase(start, s2.length());
        cout << s1 << '\n';
    } else {
        cout << "Substring not found!\n";
    } 
}

// Task 2
void insertion_C(char s1[])
{
    char s2[] = "hile";
    char c[] = "w";
    char* p = strstr(s1, c);
    char s3[128] = "\0"; // additional string forstoring the tail

    if(p && ((strlen(s1) + strlen(s2)) < 128)) {
        p += 1;             // moving to one index right
        strcpy(s3, p);      // save the tail 
        strcpy(p, s2);      // paste s2 instead of the tail
        p = p + strlen(s2); // move pointer to the end of the string
        strcpy(p, s3);      // append the tail
        cout << s1 << '\n';
    } else {
        printf("Character not found!\n");
    }
}

void insertion_Cpp(string& s1)
{
    string s2 = "hile";
    string c = "w";
    size_t start = s1.find(c);

    if(start != string::npos) {
        s1.insert(start+1, s2);
        cout << s1 << '\n';
    } else {
        cout << "Character not found!\n";
    }
}

// Task 3
void copy_C(char s[])
{
    char x[4];
    char* p = s + 3; // setting the pointer to 4th position

    if(p && strlen(s) >= 6) {
        strncpy(x, p, 3);    // copypaste 3 symbols into x
        printf("%s\n", x);
    } else {
        printf("The string is too short!\n");
    }
}

void copy_Cpp(string& s)
{
    string x;

    if(s.length() >= 6) {
       x = s.substr(3, 3); 
       cout << x << '\n';
    } else {
       cout << "The string is too short!\n"; 
    }
}

// Task 4
void delete_C(char s[])
{
    char c1 = 'm', c2 = 'f';
    int i = 0, j = 0;
    while(s[i]) {
        if(s[i] == c1 || s[i] == c2) {
            i++;
        } else {
            s[j] = s[i];
            i++; j++;
        }
    }
    s[j] = '\0';
    printf("%s\n", s);
}

void delete_Cpp(string s)
{
    char c1 = 'm', c2 = 'f';
    int i = 0;
    while(i < s.length()) {
        if(s[i] == c1 || s[i] == c2) {
            s.erase(i, 1); // erase s[i]
        } else {
            i++;
        }
    }
    cout << s << '\n';
}

int main()
{
    char s1[] = "123456 w typeertyu read mff"; // C style
    string s2 = "123456 w typeertyu read mff"; // C++ style
    bool flag = true; // state variable
    char action;

    cout << "Given string: " << s1 << '\n';
    while(flag) {
        cout << "Select task to do (1-4): ";
        cin >> action;
        switch (action) {
            case '1':
                cout << "C version: ";
                remove_C(s1); 
                cout << "C++ version: ";
                remove_Cpp(s2);
                break;
            case '2':
                cout << "C version: ";
                insertion_C(s1);
                cout << "C++ version: ";
                insertion_Cpp(s2);
                break;
            case '3':
                cout << "C version: ";
                copy_C(s1);
                cout << "C++ version: ";
                copy_Cpp(s2);
                break;
            case '4':
                cout << "C version: ";
                delete_C(s1);
                cout << "C++ version: ";
                delete_Cpp(s2);
                break;
            default:
                flag = false; // any other input stops the cycle
        }
    }
}
