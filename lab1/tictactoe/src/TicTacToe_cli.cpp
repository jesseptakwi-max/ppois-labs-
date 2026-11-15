
#include "TicTacToe.h"

#include <iostream>
#include <limits>

namespace {

void printBoard(const TicTacToe& game) {
    const std::size_t boardSize = game.size();

    std::cout << '\n';

    for (std::size_t row = 0; row < boardSize; ++row) {
        for (std::size_t column = 0; column < boardSize; ++column) {
            char cell = game[row][column];

            if (cell == ' ') {
                cell = '.';
            }

            std::cout << cell;

            if (column + 1 < boardSize) {
                std::cout << " | ";
            }
        }

        std::cout << '\n';

        if (row + 1 < boardSize) {
            for (std::size_t column = 0; column < boardSize; ++column) {
                std::cout << "--";

                if (column + 1 < boardSize) {
                    std::cout << "+";
                }
            }

            std::cout << '\n';
        }
    }

    std::cout << '\n';
}

void printMenu() {
    std::cout << "\n=== TIC-TAC-TOE MENU ===\n"
              << "1. Start new game\n"
              << "2. Choose board size\n"
              << "3. Instructions\n"
              << "0. Exit\n"
              << "Choice: ";
}

void printInstructions() {
    std::cout << "\n=== INSTRUCTIONS ===\n"
              << "Two players take turns.\n"
              << "Player X goes first.\n"
              << "Player O goes second.\n"
              << "Enter row and column numbers starting from 0.\n"
              << "The first player to complete a row, column,\n"
              << "or diagonal wins.\n"
              << "If the board fills with no winner, the game is a draw.\n";
}

bool playGame(std::size_t boardSize) {
    TicTacToe game(boardSize);
    char player = 'X';

    while (true) {
        printBoard(game);

        const char winner = game.checkWinner();

        if (winner != ' ') {
            std::cout << "Player " << winner << " wins!\n";
            break;
        }

        if (game.isFull()) {
            std::cout << "It's a draw!\n";
            break;
        }

        std::size_t row;
        std::size_t column;

        std::cout << "Player " << player
                  << ", enter row and column (0-based): ";

        if (!(std::cin >> row >> column)) {
            if (std::cin.eof()) {
                return false;
            }

            std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (!game.canPlace(row, column)) {
            std::cout << "Invalid move. Try again.\n";
            continue;
        }

        game.set(row, column, player);
        player = (player == 'X') ? 'O' : 'X';
    }

    std::cout << "\nFinal board:\n";
    printBoard(game);

    return true;
}

bool readBoardSize(std::size_t& boardSize) {
    std::cout << "Enter board size (minimum 2): ";

    if (!(std::cin >> boardSize) || boardSize < 2 ||
        boardSize > 100) {
        std::cout << "Invalid board size. Choose a value from 2 to 100.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        return false;
    }

    return true;
}

}

int main() {
    std::size_t boardSize = 3;

    while (true) {
        printMenu();

        int choice;

        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }

            std::cout << "Invalid menu input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            if (!playGame(boardSize)) {
                return 0;
            }
            break;

        case 2:
            readBoardSize(boardSize);
            break;

        case 3:
            printInstructions();
            break;

        case 0:
            std::cout << "Goodbye!\n";
            return 0;

        default:
            std::cout << "Unknown choice. Try again.\n";
            break;
        }
    }

    return 0;
}
