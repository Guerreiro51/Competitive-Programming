#include <bits/stdc++.h>

using namespace std;

vector<int> kmp(string text, string pattern) {
    vector<int> matches;

    // kmp preprocessing, calculates the length of the borders of the pattern
    // i.e., the number of characters in the beginning and end of the string
    // that are the same for each substring up to i
    vector<int> borders(pattern.size() + 1);
    borders[0] = -1;
    for (int i = 0, j = -1; i < (int)pattern.size();) {
        while (j != -1 && pattern[i] != pattern[j]) {
            j = borders[j];
        }
        i++;
        j++;
        borders[i] = j;
    }

    // finds the pattern in the text in a efficient way using the borders
    // i.e., whenever there is a mismatch, we don't need to check the whole
    // thing again, we can just move back to the border and we'll consider
    // the greatest partial match, avoiding a lot of unnecessary comparisons
    for (int i = 0, j = 0; i < (int)text.size();) {
        while (j != -1 && text[i] != pattern[j])
            j = borders[j];
        i++;
        j++;
        if (j == (int)pattern.size()) {
            matches.emplace_back(i - j);
            j = borders[j];
        }
    }
    return matches;
}

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        string text, pattern;
        cin >> text >> pattern;

        vector<int> matches = kmp(text, pattern);
        if (matches.size()) {
            cout << matches.size() << '\n';
            for (const auto& match : matches)
                cout << match + 1 << ' ';
            cout << "\n\n";

        } else
            cout << "Not Found\n\n";
    }
}