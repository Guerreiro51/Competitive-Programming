#include <bits/stdc++.h>

using namespace std;

/* Returns if it is possible to cover everyhouse with at most maxDist using numberOfAcessPoints*/
bool isPossible(vector<double>& houseNumbers, size_t numberOfAcessPoints, double maxDist) {
    double lastAcessPoint = -1e6;
    size_t curNumberOfAcessPoints = 0;
    for (auto houseNumber : houseNumbers) {
        if (abs(houseNumber - lastAcessPoint) > maxDist) {
            lastAcessPoint = houseNumber + maxDist;
            curNumberOfAcessPoints++;
        }
    }
    return curNumberOfAcessPoints <= numberOfAcessPoints;
}

/* Does a Binary Search on the minimal distance */
double minDistFromAcessPoint(vector<double>& houseNumbers, size_t numberOfAcessPoints) {
    const double EPS = 1e-3;  // we only care about the precision of the first decimal place

    double minDist = 0.0, maxDist = houseNumbers.back(), middle;
    while (maxDist - minDist > EPS) {
        middle = (minDist + maxDist) / 2.0;
        if (isPossible(houseNumbers, numberOfAcessPoints, middle))
            maxDist = middle;
        else
            minDist = middle;
    }
    return middle;
}

int main() {
    ios::sync_with_stdio(false);       // fast io
    cin.tie(nullptr);                  // fast io
    cout << fixed << setprecision(1);  // necessary precision

    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t numberOfAcessPoints;
        cin >> numberOfAcessPoints;

        size_t numberOfHouses;
        cin >> numberOfHouses;

        vector<double> houseNumbers(numberOfHouses);

        for (auto& houseNumber : houseNumbers)
            cin >> houseNumber;

        sort(houseNumbers.begin(), houseNumbers.end());

        cout << minDistFromAcessPoint(houseNumbers, numberOfAcessPoints) << '\n';
    }

    return 0;
}
