#include <bits/stdc++.h>

using namespace std;

int solve(vector<int>& numbers) {
    int maxSum = accumulate(numbers.begin(), numbers.end(), 0);
    vector<vector<bool>> dp(numbers.size(), vector<bool>(maxSum + 1, false));

    // initial condition, it is possible to sum to numbers[0] using only the numbers[0]
    dp[0][numbers[0]] = true;

    for (size_t index = 1; index < numbers.size(); index++) {  // expanding the numbers in consideration
        dp[index][numbers[index]] = true;                      // we can now create a subset consisting of only number[index]
        for (size_t sum = 0; sum <= maxSum; sum++) {
            if (dp[index - 1][sum]) {
                dp[index][sum] = true;                   // create a new subset where we DON'T sum number[index]
                dp[index][sum + numbers[index]] = true;  // create a new subset where we DO sum number[index]
            }
        }
    }

    // calculate the sum of all the subsets
    int retval = 0;
    for (int sum = 0; sum <= maxSum; sum++)
        if (dp[numbers.size() - 1][sum])
            retval += sum;

    return retval;
}

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t numberOfIntegers;
        cin >> numberOfIntegers;

        vector<int> numbers(numberOfIntegers);

        for (auto& number : numbers)
            cin >> number;

        cout << solve(numbers) << '\n';
    }
}