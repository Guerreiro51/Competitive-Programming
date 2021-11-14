#include <bits/stdc++.h>

constexpr size_t BASE = 10;

using namespace std;

void generatePasswords(const vector<string>& dictionary, const string& rule, size_t rulePos, vector<string>& outputs) {
    if (rulePos == rule.size()) {
        for (size_t i = 0; i < rulePos; i++)
            cout << outputs[i];
        cout << '\n';
        return;
    }

    if (rule[rulePos] == '#') {  // use the dictionary
        for (size_t i = 0; i < dictionary.size(); i++) {
            outputs[rulePos] = dictionary[i];
            generatePasswords(dictionary, rule, rulePos + 1, outputs);
        }
    } else if (rule[rulePos] == '0') {  // use a number
        for (size_t i = 0; i < BASE; i++) {
            outputs[rulePos] = to_string(i);
            generatePasswords(dictionary, rule, rulePos + 1, outputs);
        }
    }
}
int main() {
    size_t numberOfWords;
    while (cin >> numberOfWords) {
        vector<string> words(numberOfWords);
        for (auto& word : words)
            cin >> word;

        size_t numRules;
        cin >> numRules;

        cout << "--\n";
        while (numRules--) {
            string rule;
            cin >> rule;

            vector<string> outputs(rule.size());
            generatePasswords(words, rule, 0, outputs);
        }
    }
}