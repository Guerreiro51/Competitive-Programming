#include <bits/stdc++.h>

using namespace std;

int maxValuesGivenItemsAndFamily(const vector<pair<int, int>>& items, const vector<int>& weightCapacities, int maxWeightCapacity) {
    vector<vector<int>> maxValueDP(items.size() + 1, vector<int>(maxWeightCapacity + 1));
    fill(maxValueDP[0].begin(), maxValueDP[0].end(), 0);  // base case

    for (size_t curItem = 1; curItem <= items.size(); curItem++) {
        for (int curWeight = 0; curWeight <= maxWeightCapacity; curWeight++) {
            if (curWeight < items[curItem - 1].second)  // if curItem can't be carried
                maxValueDP[curItem][curWeight] = maxValueDP[curItem - 1][curWeight];
            else                                                                                                                                  // check if it's better to carry or to leave
                maxValueDP[curItem][curWeight] = max(maxValueDP[curItem - 1][curWeight],                                                          // leave it
                                                     items[curItem - 1].first + maxValueDP[curItem - 1][curWeight - items[curItem - 1].second]);  // carry it
        }
    }

    // use maxValueDP to calculate for each family member
    int retval = 0;
    for (const auto& weightCapacity : weightCapacities)
        retval += maxValueDP[items.size()][weightCapacity];
    return retval;
}
int main() {
    size_t numberOfFamilies;  // number of test cases
    cin >> numberOfFamilies;

    while (numberOfFamilies--) {
        size_t numberOfItems;  // supermarket stock
        cin >> numberOfItems;

        vector<pair<int, int>> items(numberOfItems);
        for (auto& [price, weight] : items)
            cin >> price >> weight;

        size_t numberOfFamilyMembers;
        cin >> numberOfFamilyMembers;

        // How much each family member can carry
        vector<int> weightCapacities(numberOfFamilyMembers);
        int maxWeight = 0;
        for (auto& weightCapacity : weightCapacities) {
            cin >> weightCapacity;
            maxWeight = max(maxWeight, weightCapacity);
        }

        cout << maxValuesGivenItemsAndFamily(items, weightCapacities, maxWeight) << '\n';
    }

    return 0;
}