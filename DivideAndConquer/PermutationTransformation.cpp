#include <bits/stdc++.h>

using namespace std;

constexpr size_t MAX = 100;
int depth[MAX + 1];

/**
 * Builds a tree from the given permutation. 
 * Note that leftIndex is inclusive and rightIndex is exclusive.
 */
void buildTree(vector<int>& permutation, int leftIndex, int rightIndex, int curDepth) {
    if (leftIndex >= rightIndex)
        return;

    auto maxIterator = max_element(permutation.begin() + leftIndex, permutation.begin() + rightIndex);
    int maxIndex = static_cast<int>(maxIterator - permutation.begin());

    depth[maxIndex] = curDepth;

    // build the left subtree
    buildTree(permutation, leftIndex, maxIndex, curDepth + 1);

    // build the right subtree
    buildTree(permutation, maxIndex + 1, rightIndex, curDepth + 1);
}

int main() {
    int numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        int permutationLength;
        cin >> permutationLength;

        vector<int> permutation(permutationLength);
        for (auto& number : permutation)
            cin >> number;

        buildTree(permutation, 0, permutationLength, 0);
        for (int i = 0; i < permutationLength; i++) {
            cout << depth[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}