#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t numberOfCities, numberOfRoads;
    cin >> numberOfCities >> numberOfRoads;

    vector<int> numberOfConnections(numberOfCities + 1, 0);

    while (numberOfRoads--) {
        int city1, city2;
        cin >> city1 >> city2;
        numberOfConnections[city1]++;
        numberOfConnections[city2]++;
    }

    for (int i = 0; i < numberOfCities; i++)
        cout << numberOfConnections[i + 1] << '\n';

    return 0;
}