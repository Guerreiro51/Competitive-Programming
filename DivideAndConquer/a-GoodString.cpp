#include <bits/stdc++.h>

using namespace std;

inline int makeAllSame(string& str, char& c) {
    return str.size() - count(str.begin(), str.end(), c);
}

int makeGoodString(string& str, char c) {
    if (str.length() == 1)
        return (int)(str[0] != c);

    string leftSubStr = str.substr(0, str.length() / 2);
    string rightSubStr = str.substr(str.length() / 2, str.length() / 2);
    char d = (c - 'a' + 1) % 26 + 'a';

    // left substr must be all c and right substr must be (c+1)-good
    size_t left = makeAllSame(leftSubStr, c) + makeGoodString(rightSubStr, d);

    // right substr must be c-good and left substr must be (c+1)-good
    size_t right = makeGoodString(leftSubStr, d) + makeAllSame(rightSubStr, c);

    return min(left, right);
}

int main() {
    int numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t strLength;
        cin >> strLength;

        string str;
        cin >> str;

        cout << makeGoodString(str, 'a') << '\n';
    }
    return 0;
}