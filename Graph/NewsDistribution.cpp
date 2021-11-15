#include <bits/stdc++.h>

using namespace std;

using AdjList = vector<size_t>;
using Graph = vector<AdjList>;

void findUsersReach(const Graph& network) {
    vector<int64_t> usersReach(network.size(), -1);
    vector<bool> reachable(network.size());

    for (size_t user = 0; user < network.size(); user++) {
        if (usersReach[user] != -1) continue;  // If the reach was already calculated, skip this user
        fill(reachable.begin(), reachable.end(), false);

        // use BFS to find every user that will be reached
        queue<size_t> qConnection;
        qConnection.emplace(user);
        reachable[user] = 1;
        while (!qConnection.empty()) {
            size_t from = qConnection.front();
            qConnection.pop();
            for (const auto& to : network[from]) {
                if (!reachable[to]) {
                    reachable[to] = true;
                    qConnection.push(to);
                }
            }
        }

        // mark every reached user with the collective reach
        int64_t reach = count(reachable.begin(), reachable.end(), true);
        for (size_t i = 0; i < network.size(); i++)
            usersReach[i] = reachable[i] ? reach : usersReach[i];
    }

    // print out every reach
    for (size_t i = 0; i < network.size(); i++)
        cout << usersReach[i] << " ";
    cout << '\n';
}

int main() {
    size_t numberOfUsers, numberOfGroups;
    cin >> numberOfUsers >> numberOfGroups;

    Graph network(numberOfUsers);
    while (numberOfGroups--) {
        size_t groupSize;
        cin >> groupSize;
        vector<size_t> groupMembers(groupSize);
        for (auto& groupMember : groupMembers) {
            cin >> groupMember;
            groupMember--;  // -- to make it a 0-indexed list
        }

        // build all the connections for the specified group
        for (size_t i = 0; i < groupMembers.size(); i++) {
            for (size_t j = i + 1; j < groupMembers.size(); j++) {
                network[groupMembers[i]].push_back(groupMembers[j]);
                network[groupMembers[j]].push_back(groupMembers[i]);
            }
        }
    }

    findUsersReach(network);

    return 0;
}