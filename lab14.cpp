#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

map<char, vector<string>> grammar;
vector<string> steps;

bool isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

int findLeftmost(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (isNonTerminal(s[i])) return i;
    }
    return -1;
}

void parseGrammar(string input) {
    for (int i = 0; i < input.length(); i++) {
        if (isNonTerminal(input[i]) && i + 2 < input.length() && 
            input[i+1] == '-' && input[i+2] == '>') {
            
            char nt = input[i];
            i += 3; // skip ->
            
            vector<string> rules;
            string rule = "";
            
            while (i < input.length() && input[i] != ',') {
                if (input[i] == '|') {
                    if (!rule.empty()) rules.push_back(rule);
                    rule = "";
                } else if (input[i] != ' ') {
                    rule += input[i];
                }
                i++;
            }
            if (!rule.empty()) rules.push_back(rule);
            
            grammar[nt] = rules;
        }
    }
}

void showGrammar() {
    cout << "\n=== Grammar ===" << endl;
    for (auto p : grammar) {
        cout << p.first << " -> ";
        for (int i = 0; i < p.second.size(); i++) {
            cout << p.second[i];
            if (i < p.second.size() - 1) cout << " | ";
        }
        cout << endl;
    }
}

bool derive(string curr, string target, int depth) {
    steps.push_back(curr);
    
    if (findLeftmost(curr) == -1) {
        return curr == target;
    }
    
    if (depth > 50) return false;
    
    int pos = findLeftmost(curr);
    char nt = curr[pos];
    
    if (grammar.find(nt) == grammar.end()) return false;
    
    for (string rule : grammar[nt]) {
        if (rule == "#") rule = "";
        
        string next = curr.substr(0, pos) + rule + curr.substr(pos + 1);
        
        if (derive(next, target, depth + 1)) {
            return true;
        }
    }
    
    steps.pop_back();
    return false;
}

void showSteps() {
    cout << "\n=== Derivation ===" << endl;
    for (int i = 0; i < steps.size(); i++) {
        cout << steps[i] << endl;
        if (i < steps.size() - 1) cout << "=> ";
    }
}

int main() {
    string input, target;
    char start;
    
    cout << "Grammar: ";
    getline(cin, input);
    
    parseGrammar(input);
    showGrammar();
    
    cout << "\nStart: ";
    cin >> start;
    
    cout << "Target: ";
    cin >> target;
    
    steps.clear();
    string s(1, start);
    
    if (derive(s, target, 0)) {
        cout << "\nSuccess!\n";
        showSteps();
    } else {
        cout << "\nFailed!\n";
    }
    
    return 0;
}