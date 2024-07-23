#include <iostream>

const int SIZE = 3;
char board[SIZE][SIZE];
//char currentPlayer;
char human = 'X';
char ai = 'O';

void initBoard() {
    for(unsigned int i = 0; i < SIZE; ++i)
        for(unsigned int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
}

void displayBoard() {
    std::cout << "   0 1 2"<<std::endl;
    for(unsigned int i = 0; i < SIZE; ++i) {
        std::cout << i << " ";
        for(unsigned int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j];
            if(j < SIZE - 1) std::cout << "|";
        }
        std::cout << std::endl;
        if(i < SIZE - 1) std::cout << "  -+-+-" << std::endl;
    }
}

bool isWin(char player) {
    for(unsigned int i = 0; i < SIZE; ++i) {
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool isDraw() {
    for(unsigned int i = 0; i < SIZE; ++i)
        for(unsigned int j = 0; j < SIZE; ++j)
            if(board[i][j] == ' ') return false;
    return true;
}

int evaluate() {
    if (isWin(ai)) return 10;
    if (isWin(human)) return -10;
    return 0;
}

int minimax(bool isMaximizing) {
    int score = evaluate();
    if(score == 10 || score == -10) return score;
    if(isDraw()) return 0;
    if(isMaximizing) {
        int best = -1000;
        for(unsigned int i = 0; i < SIZE; ++i) {
            for(unsigned int j = 0; j < SIZE; ++j) {
                if(board[i][j] == ' ') {
                    board[i][j] = ai;
                    best = std::max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;
        for(int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if(board[i][j] == ' ') {
                    board[i][j] = human;
                    best = std::min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

std::pair<int, int> findBestMove() {
    int bestVal = -1000;
    std::pair<int, int> bestMove = std::make_pair<int, int>(-1, -1);
    for(int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if(board[i][j] == ' ') {
                board[i][j] = ai;
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if(moveVal > bestVal) {
                    //bestMove = std::make_pair<int, int>(i, j);
                    bestMove.first = i;
                    bestMove.second = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void playerMove() {
    unsigned int row, col;
    std::cout << "Player is " << human << ". Please enter your coordinate to make a move on (r, c): ";
    std::cin >> row >> col;
    while (board[row][col] != ' ' || row <0 || row >= SIZE || col < 0 || col >= SIZE) {
        std::cout << "Tried an invalid move. Try again: ";
        std::cin >> row >> col;
    }
    board[row][col] = human;
}

void aiMove() {
    std::pair<int, int> bestMove = findBestMove();
    board[bestMove.first][bestMove.second] = ai;
}

int main(int, char**){
    char playAgain;
    do {
        initBoard();
        while(true) {
            displayBoard();
            playerMove();
            if(isWin(human)) {
                displayBoard();
                std::cout << "Player "<<human <<" wins." <<std::endl;
                break;
            }
            if(isDraw()) {
                displayBoard();
                std::cout << "Game ended in a draw." << std::endl;
                break;
            }
            aiMove();
            if(isWin(ai)) {
                displayBoard();
                std::cout << "Player "<< ai << " wins." <<std::endl;
                break;
            }
            if(isDraw()) {
                displayBoard();
                std::cout << "Game ended in a draw." << std::endl;
                break;
            }
        }
        std::cout << "Play again? (y for yes): " << std::endl;
        std::cin >> playAgain;
    }
    while (playAgain == 'y');
    return 0;
}
