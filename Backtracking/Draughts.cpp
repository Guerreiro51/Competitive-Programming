#include <iostream>

using namespace std;

constexpr int BOARD_SIZE = 10;

/* All 8 moves */
int moves[4][2] = {{1, -1},    // right up
                   {1, 1},     // right down
                   {-1, 1},    // left down
                   {-1, -1}};  // left up

inline bool isValidSquare(int posX, int posY) {
    return (posX >= 0 && posY >= 0 && posX < BOARD_SIZE && posY < BOARD_SIZE);
}

/* Return the longest capture chain for a white piece at posX posY*/
int findCaptures(string board[], int posX, int posY, int curCaptureCount) {
    int retval = curCaptureCount;
    for (int* move : moves) {
        // Check if there's a piece to capture
        int blackPosX = posX + move[0];
        int blackPosY = posY + move[1];
        if (!isValidSquare(blackPosX, blackPosY)) continue;
        if (board[blackPosY][blackPosX] != 'B') continue;

        // Check if the piece is capturable
        int newPosX = blackPosX + move[0];
        int newPosY = blackPosY + move[1];
        if (!isValidSquare(newPosX, newPosY)) continue;
        if (board[newPosY][newPosX] != '#') continue;

        // Capture it
        board[posY][posX] = '#';
        board[blackPosY][blackPosX] = '#';
        board[newPosY][newPosX] = 'W';

        // Recursively look for others captures
        // Max here makes sure we get the longest capture chain after every possible move
        retval = max(retval, findCaptures(board, newPosX, newPosY, curCaptureCount + 1));

        // backtrack the capture
        board[posY][posX] = 'W';
        board[blackPosY][blackPosX] = 'B';
        board[newPosY][newPosX] = '#';
    }
    return retval;
}

int main() {
    int numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        string board[BOARD_SIZE];

        for (auto& row : board)
            cin >> row;

        // look for the longest capture chain for every white piece, take the longest one
        int numberOfCaptures = 0;
        for (int y = 0; y < BOARD_SIZE; y++)
            for (int x = 0; x < BOARD_SIZE; x++)
                if (board[y].at(x) == 'W')
                    numberOfCaptures = max(numberOfCaptures, findCaptures(board, x, y, 0));

        cout << numberOfCaptures << '\n';
    }
    
    return 0;
}