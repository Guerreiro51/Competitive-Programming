#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
    size_t numberOfBadges;
    cin >> numberOfBadges;

    // Creates a vector of all the badges and sorts it
    vector<int> badges(numberOfBadges);
    for (auto& badge : badges)
        cin >> badge;
    sort(badges.begin(), badges.end());

    // Make a greedy upgrade of the badges whenever necessary
    int numberOfCoins = 0;
    for (size_t i = 1; i < badges.size(); i++) {
        if (badges[i - 1] >= badges[i]) {
            numberOfCoins += badges[i - 1] - badges[i] + 1;
            badges[i] = badges[i - 1] + 1;
        }
    }

    cout << numberOfCoins;
    return 0;
}