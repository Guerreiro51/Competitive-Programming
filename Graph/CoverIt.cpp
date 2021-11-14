#include <bits/stdc++.h>

using namespace std;

using AdjList = vector<uint32_t>;
using Graph = vector<AdjList>;

void dfs(Graph& graph, size_t parent, size_t grandParent, vector<char>& color) {
    color[parent] = (color[grandParent] == 'w') ? 'b' : 'w';  // paints black or white depending on the grandParent

    for (auto child : graph[parent])
        if (color[child] == 'r')
            dfs(graph, child, parent, color);
}

vector<char> vertex_coloring(Graph& graph, size_t numberOfVertices) {
    vector<char> color(numberOfVertices, 'r');  // starts everybody red

    for (size_t vertice = 0; vertice < numberOfVertices; vertice++)
        if (color[vertice] == 'r')
            dfs(graph, vertice, 0, color);

    return color;
}

void show_smallest_color_group(vector<char> color, size_t numberOfVertices) {
    size_t numberOfWhite = count(color.begin(), color.end(), 'w');
    size_t numberOfBlack = numberOfVertices - numberOfWhite;

    char colorToShow = (numberOfWhite < numberOfBlack) ? 'w' : 'b';

    cout << min(numberOfWhite, numberOfBlack) << '\n';
    for (size_t i = 0; i < numberOfVertices; i++)
        if (color[i] == colorToShow)
            cout << i + 1 << ' ';
    cout << '\n';
}

int main() {
    size_t numberOfQueries;
    cin >> numberOfQueries;

    while (numberOfQueries--) {
        size_t numberOfVertices, numberOfEdges;
        cin >> numberOfVertices >> numberOfEdges;

        Graph graph(numberOfVertices);
        while (numberOfEdges--) {
            size_t u, v;
            cin >> u >> v;
            graph[--u].push_back(--v);  // using -- to make it a 0-indexed list
            graph[v].push_back(u);
        }

        vector<char> color = vertex_coloring(graph, numberOfVertices);

        show_smallest_color_group(color, numberOfVertices);

        while (--numberOfVertices) {
            graph[numberOfVertices].clear();
        }
    }
}