#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST, FOLLOW;
map<pair<char,char>, string> table;
set<char> nonTerminals, terminals;
char startSymbol;

/* ---------- FIRST ---------- */
void findFirst(char X) {
    if (!FIRST[X].empty()) return;

    for (string prod : grammar[X]) {
        if (prod == "#") {
            FIRST[X].insert('#');
            continue;
        }

        for (char c : prod) {
            if (!isupper(c)) {
                FIRST[X].insert(c);
                break;
            } else {
                findFirst(c);
                for (char f : FIRST[c])
                    if (f != '#') FIRST[X].insert(f);

                if (!FIRST[c].count('#')) break;
            }
        }
    }
}

/* ---------- FOLLOW ---------- */
void findFollow() {
    FOLLOW[startSymbol].insert('$');

    bool changed = true;
    while (changed) {
        changed = false;
        for (auto g : grammar) {
            char A = g.first;
            for (string prod : g.second) {
                for (int i = 0; i < prod.size(); i++) {
                    char B = prod[i];
                    if (isupper(B)) {
                        bool epsilon = true;
                        for (int j = i + 1; j < prod.size(); j++) {
                            char beta = prod[j];
                            if (!isupper(beta)) {
                                changed |= FOLLOW[B].insert(beta).second;
                                epsilon = false;
                                break;
                            } else {
                                for (char f : FIRST[beta])
                                    if (f != '#')
                                        changed |= FOLLOW[B].insert(f).second;
                                if (!FIRST[beta].count('#')) {
                                    epsilon = false;
                                    break;
                                }
                            }
                        }
                        if (epsilon) {
                            for (char f : FOLLOW[A])
                                changed |= FOLLOW[B].insert(f).second;
                        }
                    }
                }
            }
        }
    }
}

/* ---------- Parsing Table ---------- */
void buildParsingTable() {
    for (auto g : grammar) {
        char A = g.first;
        for (string prod : g.second) {
            set<char> firstAlpha;
            if (prod == "#") firstAlpha.insert('#');
            else {
                for (char c : prod) {
                    if (!isupper(c)) {
                        firstAlpha.insert(c);
                        break;
                    } else {
                        for (char f : FIRST[c])
                            if (f != '#') firstAlpha.insert(f);
                        if (!FIRST[c].count('#')) break;
                    }
                }
            }

            for (char t : firstAlpha)
                if (t != '#')
                    table[{A, t}] = prod;

            if (firstAlpha.count('#'))
                for (char f : FOLLOW[A])
                    table[{A, f}] = "#";
        }
    }
}

/* ---------- LL(1) Parser ---------- */
bool parseInput(string input) {
    stack<char> st;
    st.push('$');
    st.push(startSymbol);
    input += "$";

    int ptr = 0;

    cout << "\nParsing Steps:\n";
    cout << "Stack\t\tInput\t\tAction\n";

    while (!st.empty()) {
        string stackContent = "";
        stack<char> temp = st;
        while (!temp.empty()) {
            stackContent += temp.top();
            temp.pop();
        }

        string inputLeft = input.substr(ptr);

        char top = st.top();
        char current = input[ptr];

        if (top == current && top == '$') {
            cout << stackContent << "\t\t" << inputLeft << "\t\tAccept\n";
            return true;
        }

        if (!isupper(top)) { // terminal
            if (top == current) {
                cout << stackContent << "\t\t" << inputLeft << "\t\tMatch " << top << "\n";
                st.pop();
                ptr++;
            } else {
                cout << stackContent << "\t\t" << inputLeft << "\t\tError! Expected " << top << "\n";
                return false;
            }
        } else { // non-terminal
            if (table.count({top, current})) {
                string prod = table[{top, current}];
                cout << stackContent << "\t\t" << inputLeft << "\t\t" << top << "->" << prod << "\n";
                st.pop();
                if (prod != "#") {
                    for (int i = prod.size()-1; i >= 0; i--)
                        st.push(prod[i]);
                }
            } else {
                cout << stackContent << "\t\t" << inputLeft << "\t\tError! No rule\n";
                return false;
            }
        }
    }
    return false;
}

/* ---------- MAIN ---------- */
int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (use # for epsilon):\n";
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        char lhs = s[0];
        if (i == 0) startSymbol = lhs;
        nonTerminals.insert(lhs);

        string rhs = s.substr(2), temp = "";
        for (char c : rhs) {
            if (c == '|') {
                grammar[lhs].push_back(temp);
                temp.clear();
            } else temp += c;
        }
        grammar[lhs].push_back(temp);
    }

    // Collect terminals
    for (auto g : grammar)
        for (string p : g.second)
            for (char c : p)
                if (!isupper(c) && c != '#')
                    terminals.insert(c);
    terminals.insert('$');

    // Compute FIRST and FOLLOW
    for (char nt : nonTerminals) findFirst(nt);
    findFollow();
    buildParsingTable();

    cout << "\nEnter input string to parse: ";
    string input;
    cin >> input;

    bool success = parseInput(input);
    if (success)
        cout << "\nInput string is Accepted by the Grammar.\n";
    else
        cout << "\nInput string is Rejected by the Grammar.\n";

    return 0;
}
