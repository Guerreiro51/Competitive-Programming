#include <bits/stdc++.h>

using namespace std;

/* Custom string compare */
bool compareString(string a, string b) {
    if (a.size() == b.size()) return a < b;
    return a.size() < b.size();
}

using WordSet = set<string, decltype(compareString)*>;

/* All 8 moves */
int moves[8][2] = {{1, 0},    // right
                   {1, 1},    // right down
                   {0, 1},    // down
                   {-1, 1},   // left down
                   {-1, 0},   // left
                   {-1, -1},  // left up
                   {0, -1},   // up
                   {1, -1}};  // right up

/* Check if a position is valid in the matrix */
inline bool isValidPos(int pos, int maxSize) {
    return (pos >= 0 && pos < maxSize);
}

/* Find every word starting at posX posY. Have to call it n^2 times */
void findWords(vector<string>& matrix, WordSet& words, string& curWord, int posX, int posY) {
    char curChar = matrix[posY][posX];
    curWord.push_back(curChar);

    if (curWord.size() >= 3)
        words.insert(curWord);

    for (int* move : moves) {
        int newPosX = posX + move[0];
        if (!isValidPos(newPosX, matrix.size())) continue;

        int newPosY = posY + move[1];
        if (!isValidPos(newPosY, matrix.size())) continue;

        char nextChar = matrix[newPosY][newPosX];
        if (curChar < nextChar)
            findWords(matrix, words, curWord, newPosX, newPosY);
    }
    curWord.pop_back();
}

/* Calls findWords for every starting position (n^2 times)*/
void findAllWords(vector<string>& matrix, WordSet& words) {
    string word;
    for (int i = 0; i < (int)matrix.size(); i++)
        for (int j = 0; j < (int)matrix.size(); j++)
            findWords(matrix, words, word, i, j);
}

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t matrixSize;
        cin >> matrixSize;
        vector<string> matrix(matrixSize);

        for (auto& str : matrix)
            cin >> str;

        WordSet words(compareString);
        findAllWords(matrix, words);

        for (auto& word : words)
            cout << word << '\n';

        if (numberOfTestCases)
            cout << '\n';
    }

    return 0;
}