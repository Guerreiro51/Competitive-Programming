#include <bits/stdc++.h>

using namespace std;

constexpr int LIMIT = 1e9 + 7;

int produceNumberOfWays(const vector<int>& coins, size_t desiredSum, size_t numberOfCoins) {
    vector<int> numberOfWays(desiredSum + 1, 0);
    numberOfWays[0] = 1;  // base case

    for (size_t curDesiredSum = 1; curDesiredSum <= desiredSum; curDesiredSum++)                                   // Find all number of ways up to the desiredSum
        for (size_t coinIndex = 0; coinIndex < numberOfCoins; coinIndex++) {                                       // Try using each coin on the curDesiredSum
            int remainingSum = curDesiredSum - coins[coinIndex];                                                   // Check how much remains if we use the coin from coinIndex
            if (remainingSum >= 0)                                                                                 // If it is a valid remaining, i.e., we haven't gone past the curDesiredSum
                numberOfWays[curDesiredSum] = (numberOfWays[curDesiredSum] + numberOfWays[remainingSum]) % LIMIT;  // we've found numberOfWays[remainingSum] new ways of computing the curDesiredSum*/
        }
    return numberOfWays[desiredSum];  // return the number of ways to sum to desiredSum
}

int main() {
    size_t numberOfCoins, desiredSum;
    cin >> numberOfCoins >> desiredSum;

    vector<int> coins(numberOfCoins);
    for (auto& coin : coins)
        cin >> coin;

    cout << produceNumberOfWays(coins, desiredSum, numberOfCoins);

    return 0;
}