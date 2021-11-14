#include <bits/stdc++.h>

using namespace std;

// longest non increasing subsequence
int lnis(vector<int>& numbers) {
    vector<int> dp(numbers.size());
    dp[0] = 1;

    for (size_t i = 1; i < numbers.size(); i++) {  // considering every sequence that ends with i
        dp[i] = 1;
        // for every other number before the ith, try including it if it is bigger or equal than the ith
        for (int j = i - 1; j >= 0; j--) {
            if (numbers[j] >= numbers[i])
                dp[i] = max(dp[j] + 1, dp[i]);
        }
    }

    return *max_element(dp.begin(), dp.end());  // return the longest
}

int main() {
    for (int testCase = 1; true; testCase++) {
        bool anotherTestCase = false;
        vector<int> missiles;
        while (true) {
            int height;
            cin >> height;

            if (height == -1) {
                break;
            }
            // print one additional new line after every testcase except the last one
            if(testCase != 1 && !anotherTestCase)
                cout << '\n';
            anotherTestCase = true;
            missiles.push_back(height);
        }
        if (!anotherTestCase)
            break;

        cout << "Test #" << testCase << ":\n";
        cout << "  maximum possible interceptions: " << lnis(missiles) << "\n";
    }

    return 0;
}