#include <bits/stdc++.h>

// Some constants related to the problem
constexpr size_t SIZE_OF_THE_SEQUENCE = 6;
constexpr int sequence[SIZE_OF_THE_SEQUENCE] = {4, 8, 15, 16, 23, 42};

using namespace std;

int main() {
    // Create a map so we know the index of a number quickly and initialize the frequency array
    unordered_map<int, size_t> numberIndex;
    ulong frequency[SIZE_OF_THE_SEQUENCE];
    for (size_t i = 0; i < SIZE_OF_THE_SEQUENCE; i++) {
        numberIndex[sequence[i]] = i;
        frequency[i] = 0;
    }

    size_t numberOfElements;
    cin >> numberOfElements;

    size_t numberOfDeletions = 0;
    while (numberOfElements--) {  // for each number
        int number;
        cin >> number;
        size_t curNumberIndex = numberIndex[number];  // Only the number index matters

        bool deleteNumber = false;
        for (long i = curNumberIndex - 1; i >= 0L; i--) {
            if (!(frequency[curNumberIndex] < frequency[i])) {  //if the frequency of the numbers before are not lower, we should delete it
                deleteNumber = true;
                break;
            }
        }

        if (deleteNumber)
            numberOfDeletions++;
        else
            frequency[curNumberIndex]++;
    }

    // Delete all incomplete sequences
    // note that the frequency of the last number is the number of complete sequences, since the frequency of everyone before it is higher or equal
    for (size_t i = 0; i < SIZE_OF_THE_SEQUENCE - 1; i++)
        numberOfDeletions += (frequency[i] - frequency[SIZE_OF_THE_SEQUENCE - 1]);

    cout << numberOfDeletions;

    return 0;
}