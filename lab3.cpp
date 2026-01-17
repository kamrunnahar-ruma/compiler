#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    getline(cin, line);

    if (line.substr(0, 2) == "//")
        cout << "Single-line comment";
    else if (line.substr(0, 2) == "/*")
        cout << "Multi-line comment";
    else
        cout << "Not a comment";

    return 0;
}
