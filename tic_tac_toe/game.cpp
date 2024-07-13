#include <iostream>
#include <limits>
using namespace std;

char board[3][3];
char current_marker;
int current_player;

void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool placeMarker(int slot) {
    int row = slot / 3;
    int col = slot % 3;

    if (board[row][col] != ' ') {
        return false;
    }

    board[row][col] = current_marker;
    return true;
}

char checkWinner() {
    // Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
    }
    // Columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }

    return ' ';
}

void swapPlayerAndMarker() {
    if (current_marker == 'X') {
        current_marker = 'O';
    } else {
        current_marker = 'X';
    }

    if (current_player == 1) {
        current_player = 2;
    } else {
        current_player = 1;
    }
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

int minimax(bool isMaximizing) {
    char result = checkWinner();
    if (result == 'X') return -1;
    if (result == 'O') return 1;
    if (isBoardFull()) return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(true);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

void bestMove() {
    int bestScore = numeric_limits<int>::min();
    int move = -1;
    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;
        if (board[row][col] == ' ') {
            board[row][col] = 'O';
            int score = minimax(false);
            board[row][col] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    placeMarker(move);
}

void game(bool vsAI) {
    current_marker = 'X';
    current_player = 1;

    // Initialize the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    drawBoard();

    for (int i = 0; i < 9; i++) {
        int slot;
        if (vsAI && current_player == 2) {
            bestMove();
        } else {
            cout << "Player " << current_player << "'s turn. Enter your move (1-9): ";
            cin >> slot;
            slot--; // to make it 0-indexed

            if (slot < 0 || slot > 8 || !placeMarker(slot)) {
                cout << "Invalid move! Try again." << endl;
                i--;
                continue;
            }
        }

        drawBoard();

        char winner = checkWinner();
        if (winner != ' ') {
            cout << "Player " << (winner == 'X' ? "1" : "2") << " wins! Congratulations!" << endl;
            return;
        }

        swapPlayerAndMarker();
    }

    cout << "It's a draw!" << endl;
}

int main() {
    int mode;
    cout << "Choose game mode: \n1. Player vs Player\n2. Player vs AI\nEnter your choice: ";
    cin >> mode;

    if (mode == 1) {
        game(false);
    } else if (mode == 2) {
        game(true);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
