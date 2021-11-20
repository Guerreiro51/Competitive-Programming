#include <bits/stdc++.h>

using namespace std;

// finds the Longest Common Subsequence
size_t lcs(const pair<string, string>& strPair) {
    vector<vector<size_t>> lcsDP(strPair.first.length() + 1, vector<size_t>(strPair.second.length() + 1));

    // starting conditions
    for (size_t i = 0; i <= strPair.first.length(); i++)
        lcsDP[i][0] = 0;
    for (size_t j = 0; j <= strPair.second.length(); j++)
        lcsDP[0][j] = 0;

    // note that i and j are 1-based indexes for both strings but 0-based for the lcsDP 2D array
    for (size_t i = 1; i <= strPair.first.length(); i++) {
        for (size_t j = 1; j <= strPair.second.length(); j++) {
            lcsDP[i][j] = max(lcsDP[i - 1][j], lcsDP[i][j - 1]);  // either ignore first string's char or the second's
            if (strPair.first[i - 1] == strPair.second[j - 1])    // if they are equal, try including them into the sequence
                lcsDP[i][j] = max(lcsDP[i][j], 1 + lcsDP[i - 1][j - 1]);
        }
    }

    return lcsDP[strPair.first.length()][strPair.second.length()];
}

int main() {
    pair<string, string> strPair;
    while (getline(cin, strPair.first) && getline(cin, strPair.second))
        cout << lcs(strPair) << '\n';

    return 0;
}