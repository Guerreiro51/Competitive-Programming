#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t numberOfActivities;
        cin >> numberOfActivities;

        // endTime, startTime
        vector<pair<ulong, ulong>> activities(numberOfActivities);
        for (auto& activity : activities)
            cin >> activity.second >> activity.first;
        sort(activities.begin(), activities.end());  // sort by endTime in increasing order

        size_t numberOfActivitiesDone = 0;
        ulong lastEndTime = 0;
        for (auto& activity : activities) {
            if (activity.second >= lastEndTime) {  // check if we can schedule the current activity
                lastEndTime = activity.first;
                numberOfActivitiesDone++;
            }
        }

        cout << numberOfActivitiesDone << '\n';
    }

    return 0;
}