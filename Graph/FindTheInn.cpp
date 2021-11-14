#include <bits/stdc++.h>

using namespace std;

using adj = pair<size_t, size_t>;  // destination, weight
using AdjList = vector<adj>;
using Graph = vector<AdjList>;

size_t dijkstra(const Graph& paths, size_t numberOfVertices) {
    array<size_t, 30000> distances;
    distances.fill(ULONG_MAX / 4);  // starts everyone with infinity

    distances[0] = 0;

    priority_queue<adj> pq;
    pq.push(adj(0, 0));
    while (!pq.empty()) {
        size_t destination = pq.top().first;
        size_t distance = pq.top().second;
        pq.pop();
        if (distance > distances[destination]) continue;  // If this path doesn't lower the distance, discard

        // For every path from this newly reached destination, if there's a path such that the distance is shorter, update it and push into the pq
        for (adj path : paths[destination])
            if (distances[path.first] > distances[destination] + path.second) {
                distances[path.first] = distances[destination] + path.second;
                pq.push(adj(path.first, distances[path.first]));
            }
    }

    // In this case, we only care about the distance to the last one
    return distances[numberOfVertices - 1];
}

int main() {
    size_t numberOfAreas, numberOfPaths, timeLeft, timeLaughing, numberOfPineAreas;
    cin >> numberOfAreas >> numberOfPaths >> timeLeft >> timeLaughing >> numberOfPineAreas;

    timeLeft *= 60;  // converts to seconds

    vector<bool> pineAreas(numberOfAreas, false);
    while (numberOfPineAreas--) {
        size_t pineArea;
        cin >> pineArea;

        pineAreas[--pineArea] = true;  // -- to make it a 0-indexed list
    }

    Graph paths(numberOfAreas);
    while (numberOfPaths--) {
        size_t from, to, time;
        cin >> from >> to >> time;
        from--;
        to--;        // making it a 0-indexed list
        time *= 60;  // converts to seconds

        time += (pineAreas[to]) ? timeLaughing : 0;  // if the destination is a pineArea, increment the cost to laugh
        paths[from].push_back({to, time});
    }

    size_t minimumTime = dijkstra(paths, numberOfAreas);

    if (minimumTime <= timeLeft)
        cout << minimumTime << "\n";
    else
        cout << "-1\n";

    return 0;
}