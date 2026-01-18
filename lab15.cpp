/**
 * PROBLEM 15: Left Factoring of Grammar (Using # for epsilon)
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

/* ---------- Find common prefix of two strings ---------- */
string commonPrefix(string a, string b)
{
    int i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i])
        i++;
    return a.substr(0, i);
}

int main()
{
    map<string, vector<string>> grammar;

    // Input Grammar
    grammar["S"] = {"iEtS", "iEtSeS", "a"};
    grammar["E"] = {"b"};

    map<string, vector<string>> result;

    for (auto g : grammar)
    {
        string nt = g.first;
        vector<string> p = g.second;

        if (p.size() < 2)
        {
            result[nt] = p;
            continue;
        }

        string prefix = commonPrefix(p[0], p[1]);

        vector<string> factored, rest;

        for (auto s : p)
        {
            if (s.find(prefix) == 0)
                factored.push_back(s);
            else
                rest.push_back(s);
        }

        if (!prefix.empty() && factored.size() > 1)
        {
            string newNT = nt + "'";

            result[nt].push_back(prefix + newNT);

            for (auto r : rest)
                result[nt].push_back(r);

            for (auto f : factored)
            {
                string suf = f.substr(prefix.length());
                if (suf == "")
                    suf = "#";   // epsilon
                result[newNT].push_back(suf);
            }
        }
        else
        {
            result[nt] = p;
        }
    }

    /* ---------- Output ---------- */
    cout << "\nLeft-Factored Grammar:\n";
    for (auto g : result)
    {
        cout << g.first << " -> ";
        for (int i = 0; i < g.second.size(); i++)
        {
            cout << g.second[i];
            if (i != g.second.size() - 1)
                cout << " | ";
        }
        cout << endl;
    }

    return 0;
}
