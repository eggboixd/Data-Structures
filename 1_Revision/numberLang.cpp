#include <iostream>
#include <stack>
#include <string>

using namespace std;

char convertToAlphabet(char digit) {
    // Convert digit to alphabet character
    return 'a' + digit - '1'; // ASCII value of 'a' is 97
}

string convert(string word) {
    string result = "";

    for (int i = 0; i < word.length(); ++i) {
        if (isdigit(word[i])) {
            char alphabetChar = convertToAlphabet(word[i]);
            result += alphabetChar;
            
            // If the next character is also a digit, append '0'
            if (i + 1 < word.length() && isdigit(word[i + 1])) {
                result += '0';
            }
        } else {
            result += word[i];
        }
    }

    return result;
}


int main() {
    int n;
    cin >> n;

    stack<string> words;

    for (int i = 0; i < n; i++) {
        int size;
        string wordCode;
        cin >> wordCode;
        words.push(wordCode);
    }

    return 0;
}
