#include <bits/stdc++.h>

using namespace std;

long long solvePD(vector<long long>& toys) {
    vector<long long> DP(toys.size());

    for (int i = 0; i < 6; i++)
        DP[toys.size() - 6 + i] = 0;  // avoid segfault

    for (int curPick = toys.size() - 6 - 1; curPick >= 0; curPick--) {
        DP[curPick] = 0;

        long long sum = 0;
        for (int i = curPick, j = 2; i < min(curPick + 3, int(toys.size()) - 6); i++, j++) {
            sum += toys[i];
            DP[curPick] = max(DP[curPick], sum + DP[i + j]);
        }
    }
    long long retval = DP[0];
    return retval;
}

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t numberOfToys;
        cin >> numberOfToys;
        vector<long long> toys(numberOfToys);

        for (auto& toy : toys)
            cin >> toy;

        for (int i = 0; i < 6; i++)
            toys.emplace_back(0LL);  // avoid segfault

        cout << solvePD(toys) << '\n';
    }
}