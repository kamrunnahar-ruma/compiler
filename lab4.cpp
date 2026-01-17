#include <bits/stdc++.h>
using namespace std;

bool isValidIdentifier(string id) {
    // Check if first character is a letter or underscore
    if (!(isalpha(id[0]) || id[0] == '_'))
        return false;

    // Check the rest of the characters
    for (int i = 1; i < id.length(); i++) {
        if (!(isalnum(id[i]) || id[i] == '_'))
            return false;
    }
    string keywords[] = {
            "int", "float", "double", "char", "if", "else",
            "for", "while", "do", "return", "break", "continue",
            "class", "public", "private", "protected", "void",
            "switch", "case", "default", "static"
        };

        // Check keyword
        for (string kw : keywords) {
            if (id == kw) {
                return  false;
                break;
            }
        }

    return true;
}

int main() {
    string id;
    cout << "Enter an identifier: ";
    cin >> id;

    if (isValidIdentifier(id))
        cout << "Valid identifier";
    else
        cout << "Invalid identifier";

    return 0;
}
