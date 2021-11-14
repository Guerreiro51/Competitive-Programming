#include <math.h>

#include <iostream>
#include <map>
#include <queue>

using namespace std;

using Maze = vector<vector<int>>;
using Pos = pair<int, int>;

template <typename T, typename U>
pair<T, U> operator+(const pair<T, U>& l, const pair<T, U>& r) {
    return {l.first + r.first, l.second + r.second};
}

Pos moves[4] = {{0, 1},    // down
                {1, 0},    // right
                {0, -1},   // up
                {-1, 0}};  // left

struct State {
    Pos pos;
    int cost;
    int distFromBeg;

    State(Pos pPos, int pCost, int pDistFromBeg)
        : pos(pPos), cost(pCost), distFromBeg(pDistFromBeg) {}

    friend bool operator<(const State s1, const State s2) {
        return s1.cost > s2.cost;
    }
};

int manhattanDist(const Pos& a, const Pos& b) {
    return (abs(a.first - b.first) + abs(a.second - b.second));
}

int solveMaze(const Maze& maze, Pos startingPos, Pos desiredPos) {
    map<Pos, bool> visitedStates;

    // marks position as visited and returns if it is valid
    auto isValidPos = [&](const Pos& pos) {
        int x = pos.first, y = pos.second;
        if (x < 0 || x >= (int)maze.size() || y < 0 || y >= (int)maze.size() || !maze[x][y] || visitedStates.find(pos) != visitedStates.end())
            return false;
        visitedStates[pos] = true;
        return true;
    };

    if (!isValidPos(startingPos))
        return -1;

    priority_queue<State> pq;
    pq.emplace(startingPos, 1 + manhattanDist(startingPos, desiredPos), 1);

    while (!pq.empty()) {
        State currentState = pq.top();
        pq.pop();
        if (manhattanDist(currentState.pos, desiredPos) == 0)
            return currentState.distFromBeg;

        for (size_t i = 0; i < 4UL; i++) {
            Pos nextPos = currentState.pos + moves[i];
            if (isValidPos(nextPos))
                pq.emplace(nextPos, 1 + currentState.distFromBeg + manhattanDist(nextPos, desiredPos), currentState.distFromBeg + 1);
        }
    }

    return -1;
}

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t mazeSize;
        cin >> mazeSize;

        Maze maze(mazeSize, vector<int>(mazeSize));

        Pos startingPos, desiredPos;
        cin >> startingPos.first >> startingPos.second >> desiredPos.first >> desiredPos.second;

        for (size_t i = 0; i < mazeSize; i++)
            for (size_t j = 0; j < mazeSize; j++)
                cin >> maze[i][j];

        int pathSize = solveMaze(maze, startingPos, desiredPos);

        if (pathSize == -1)
            cout << "Caminho Inexistente." << endl;
        else
            cout << "Nro de posicoes: " << pathSize << endl;
    }

    return 0;
}