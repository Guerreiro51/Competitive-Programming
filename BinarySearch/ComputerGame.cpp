#include <bits/stdc++.h>

using namespace std;

long long batteryCharge;
long long numberOfTurns;
long long justPlayCost;
long long playChargeCost;

bool isPossible(long long numberOfJustPlays) {
    return (numberOfJustPlays * justPlayCost + (numberOfTurns - numberOfJustPlays) * playChargeCost) < batteryCharge;
}

// Finds the maximum number of just plays
long long binarySearch(long long minNumberOfJustPlays, long long maxNumberOfJustPlays) {
    long long middle;
    while (minNumberOfJustPlays < maxNumberOfJustPlays) {
        middle = (minNumberOfJustPlays + maxNumberOfJustPlays + 1) / 2;
        if (isPossible(middle))
            minNumberOfJustPlays = middle;
        else
            maxNumberOfJustPlays = middle - 1;
    }
    return minNumberOfJustPlays;
}

int main() {
    size_t numberOfQueries;
    cin >> numberOfQueries;

    while (numberOfQueries--) {
        cin >> batteryCharge;
        cin >> numberOfTurns;
        cin >> justPlayCost;
        cin >> playChargeCost;

        if (isPossible(0))
            cout << binarySearch(0, numberOfTurns) << '\n';
        else
            cout << "-1\n";
    }

    return 0;
}