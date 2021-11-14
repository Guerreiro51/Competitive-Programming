#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t numberOfSquares;
    cin >> numberOfSquares;

    vector<long> squares(numberOfSquares);
    cin >> squares[0];
    squares[0]--;

    bool isNonDecreasing = true;
    for (size_t i = 1; i < numberOfSquares; i++) {
        cin >> squares[i];

        if (squares[i] > squares[i - 1])
            squares[i]--;  // the greedy best decision in this case is to always decrease it

        // note that the square before it was already decreased if it could've been decreased. So in this case there is nothing to do
        if (squares[i] < squares[i - 1]) {
            isNonDecreasing = false;
            break;
        }
    }

    if (isNonDecreasing)
        cout << "Yes";
    else
        cout << "No";

    return 0;
}