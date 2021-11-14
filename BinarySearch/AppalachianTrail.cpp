#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Discovers the farthest campsite you can reach until the next day
int maxTravel(const vector<int>& distances, size_t currentCampsite, int threshold) {
    int distanceTraveled = 0;
    while (currentCampsite < distances.size() && distanceTraveled <= threshold)
        distanceTraveled += distances[currentCampsite++];

    if (distanceTraveled <= threshold)
        return distances.size() + 1;  // reached the endpoint
    return currentCampsite;           // next campsite index for tomorrow
}

// Searches for a path given a certain threshold, the distances between each campsite and the number of nights
bool bfs(const vector<int>& distances, int threshold, int numberOfNights) {
    vector<int> campsitesDay(distances.size() + 1, 0);
    campsitesDay[0] = 1;

    queue<size_t> nextCampsite;
    nextCampsite.push(0);

    while (!nextCampsite.empty()) {
        size_t currentCampsite = nextCampsite.front();
        nextCampsite.pop();

        if (campsitesDay[currentCampsite] <= numberOfNights + 1) {                            // give up if too many days
            size_t lastReachableCampsite = maxTravel(distances, currentCampsite, threshold);  // calculates the last reachable campsite given the threshhold
            for (size_t campsite = currentCampsite + 1; campsite < lastReachableCampsite; campsite++) {
                if (campsitesDay[campsite] == 0) {                               // if the campsite wasn't visited yet
                    campsitesDay[campsite] = campsitesDay[currentCampsite] + 1;  // visit it the next day
                    nextCampsite.push(campsite);                                 // BFS for a path given the threshold
                }
            }
        }
    }
    return campsitesDay[distances.size()] != 0;  // if we reached trails endpoint
}

// Searches for the optimal travel limit (threshold)
int binarySearch(const vector<int>& distances, int numberOfNights, int left, int right) {
    while (left < right) {
        int middle = (left + right) / 2;
        if (bfs(distances, middle, numberOfNights))
            right = middle;
        else
            left = middle + 1;
    }
    return left;
}

int main() {
    size_t numberOfCampsites;
    size_t numberOfNights;
    while (cin >> numberOfCampsites) {  // Reads the number of campsites
        cin >> numberOfNights;          // Reads the number of nights

        int totalDistance = 0;
        vector<int> distances(numberOfCampsites + 1);
        for (auto& distFromLastCampsite : distances) {
            cin >> distFromLastCampsite;
            totalDistance += distFromLastCampsite;
        }

        cout << binarySearch(distances, numberOfNights, -1, totalDistance - 1) << '\n';  // Binary searches the smallest threshold
    }
    return 0;
}