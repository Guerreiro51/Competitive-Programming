#include <bits/stdc++.h>

using namespace std;

bool tryPortion(vector<int64_t>& numberOfItems, int64_t numberOfReceivers, int64_t portionSize) {
    if (portionSize == 0)
        return true;
    int64_t numberOfPortions = 0;
    for (int64_t items : numberOfItems) {
        numberOfPortions += items / portionSize;
        if (numberOfPortions >= numberOfReceivers) return true;
    }
    return false;
}

int64_t solve(vector<int64_t>& numberOfItems, int64_t numberOfReceivers, int64_t min, int64_t max) {
    int64_t middle;
    while (min < max) {
        middle = (min + max + 1) / 2;
        if (tryPortion(numberOfItems, numberOfReceivers, middle))
            min = middle;
        else
            max = middle - 1;
    }
    
    return min;
}

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        int64_t numberOfBoxes, numberOfStudents;
        cin >> numberOfBoxes >> numberOfStudents;
        vector<int64_t> numberOfCandies(numberOfBoxes);

        int64_t totalCandies = 0;
        for (int64_t i = 0; i < numberOfBoxes; i++) {
            cin >> numberOfCandies[i];
            totalCandies += numberOfCandies[i];
        }
        sort(numberOfCandies.begin(), numberOfCandies.end(), greater<int64_t>());
        cout << solve(numberOfCandies, numberOfStudents, 0, totalCandies / numberOfStudents) << '\n';
        numberOfCandies.clear();
    }
    return 0;
}