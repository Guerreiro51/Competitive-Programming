#include <bits/stdc++.h>

constexpr int INSERT_PRICE = 1;
constexpr int REMOVE_PRICE = 1;
constexpr int REPLACE_PRICE = 1;

using namespace std;

int strDistance(const string& fixedString, const string& mutableString) {
    vector<vector<int>> strDistanceDP(fixedString.size() + 1, vector<int>(mutableString.size() + 1));

    // base cases
    for (size_t i = 0; i <= fixedString.length(); i++)  // The mutableString is missing letters
        strDistanceDP[i][0] = i * INSERT_PRICE;
    for (size_t j = 0; j <= mutableString.length(); j++)  // The mutableString has too many letters
        strDistanceDP[0][j] = j * REMOVE_PRICE;

    auto replaceChrCost = [](const char& c1, const char& c2) {
        if (c1 == c2)
            return 0;
        else
            return REPLACE_PRICE;
    };

    for (size_t i = 1; i <= fixedString.length(); i++)                                                                          // For every letter in fixedString
        for (size_t j = 1; j <= mutableString.length(); j++)                                                                    // For every letter in mutable string
            strDistanceDP[i][j] = min(min(strDistanceDP[i][j - 1] + INSERT_PRICE,                                               // try inserting
                                          strDistanceDP[i - 1][j] + REMOVE_PRICE),                                              // try removing
                                      replaceChrCost(fixedString[i - 1], mutableString[j - 1]) + strDistanceDP[i - 1][j - 1]);  // try replacing

    return strDistanceDP[fixedString.length()][mutableString.length()];
}

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        string fixedString, mutableString;
        cin >> fixedString >> mutableString;

        cout << strDistance(fixedString, mutableString) << '\n';
    }

    return 0;
}