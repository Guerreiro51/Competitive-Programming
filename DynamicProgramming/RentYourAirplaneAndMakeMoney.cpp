#include <bits/stdc++.h>

using namespace std;

constexpr size_t MAX = 1e6;

long long solve(vector<vector<pair<long, long>>>& orders, long maxTime) {
    vector<long long> DP(maxTime + 1);
    DP[0] = 0;
    for (long endTime = 1; endTime <= maxTime; endTime++) {
        DP[endTime] = DP[endTime - 1];        // starting at endTime, we can do at least as good as endTime-1
        for (auto order : orders[endTime]) {  // try to do better using orders that end at endTime
            if (endTime >= order.first)
                DP[endTime] = max(DP[endTime], order.second + DP[endTime - order.first]);
            else
                DP[endTime] = max(DP[endTime], (long long)order.second);
        }
    }
    return DP[maxTime];
}

int main() {
    // Fast IO
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t numberOfOrders;
        cin >> numberOfOrders;

        vector<vector<pair<long, long>>> orders(2 * MAX + 1);  // order[endTime] = {{duration, price}, ... }
        long maxTime = 0;
        for (size_t i = 0; i < numberOfOrders; i++) {
            long startTime, duration, price, endTime;
            cin >> startTime >> duration >> price;
            endTime = startTime + duration;

            orders[endTime].emplace_back(duration, price);
            maxTime = max(maxTime, endTime);
        }

        cout << solve(orders, maxTime) << '\n';
    }
}