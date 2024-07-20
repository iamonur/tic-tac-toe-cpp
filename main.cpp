#include <iostream>

const int SIZE = 3;
char board[SIZE][SIZE];
char currentPlayer;

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

bool isWin() {
    for(unsigned int i = 0; i < SIZE; ++i) {
        if(board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) return true;
        if(board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) return true;
    }
    if(board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) return true;
    if(board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) return true;
    return false;
}

bool isDraw() {
    for(unsigned int i = 0; i < SIZE; ++i)
        for(unsigned int j = 0; j < SIZE; ++j)
            if(board[i][j] == ' ') return false;
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void takeTurn() {
    unsigned int row, col;
    std::cout << "Player is " << currentPlayer << ". Please enter your coordinate to make a move on (r, c): ";
    std::cin >> row >> col;
    while (board[row][col] != ' ' || row <0 || row >= SIZE || col < 0 || col >= SIZE) {
        std::cout << "Tried an invalid move. Try again: ";
        std::cin >> row >> col;
    }
    board[row][col] = currentPlayer;
}

int main(int, char**){
    char playAgain;
    do {
        initBoard();
        currentPlayer = 'X';
        while(true) {
            displayBoard();
            takeTurn();
            if(isWin()) {
                displayBoard();
                std::cout << "Player "<<currentPlayer <<" wins." <<std::endl;
                break;
            }
            if(isDraw()) {
                displayBoard();
                std::cout << "Game ended in a draw." << std::endl;
                break;
            }
            switchPlayer();
        }
        std::cout << "Play again? (y for yes): " << std::endl;
        std::cin >> playAgain;
    }
    while (playAgain == 'y');
    return 0;
}
