#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);

    vector<string> operators = {
        "==", "!=", "<=", ">=", "&&", "||", "+=", "-=", "*=", "/=", "%=",
        "+", "-", "*", "/", "%", "=", "<", ">", "!"
    };

    int count = 0;
    for (size_t i = 0; i < s.length(); ) {
        bool matched = false;
        for (string op : operators) {
            if (s.substr(i, op.size()) == op) {
                count++;
                i += op.size();
                matched = true;
                break;
            }
        }
        if (!matched) i++;
    }

    cout << "Number of operators: " << count << endl;
    return 0;
}
