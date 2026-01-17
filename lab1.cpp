#include <bits/stdc++.h>
using namespace std;
int main() {
    ifstream file;
    string filename, line;
    int characters = 0, words = 0, lines = 0;
    cout << "Enter file name: ";
    cin >> filename;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Error: File cannot be opened." << endl;
        return 1;
    }
    while (getline(file, line)) {
        lines++;                       // Count lines
        characters += line.length();   // Count characters
        bool inWord = false;
        for (char ch : line) {
            if (!isspace(ch)) {
                if (!inWord) {
                    words++;
                    inWord = true;
                }
            } else {
                inWord = false;
            }
        }
    }
    file.close();
    cout << "\nCharacters: " << characters << endl;
    cout << "Words: " << words << endl;
    cout << "Lines: " << lines << endl; 
    return 0;
}
