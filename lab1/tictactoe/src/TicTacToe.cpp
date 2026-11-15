
#include "TicTacToe.h"

#include <stdexcept>
#include <utility>

// Row proxy implementation.

TicTacToe::Row::Row(std::vector<char>& cells)
    : cells_(cells) {}

char& TicTacToe::Row::operator[](std::size_t column) {
    return cells_.at(column);
}

TicTacToe::ConstRow::ConstRow(const std::vector<char>& cells)
    : cells_(cells) {}

const char& TicTacToe::ConstRow::operator[](
    std::size_t column) const {
    return cells_.at(column);
}

// Constructors and assignment.

TicTacToe::TicTacToe(std::size_t size)
    : n(size), board(size, std::vector<char>(size, ' ')) {
    if (size == 0) {
        throw std::invalid_argument("Board size must be greater than zero");
    }
}

TicTacToe::TicTacToe(const TicTacToe& other)
    : n(other.n), board(other.board) {}

TicTacToe& TicTacToe::operator=(const TicTacToe& other) {
    if (this != &other) {
        n = other.n;
        board = other.board;
    }

    return *this;
}

// Comparison operators.

bool TicTacToe::operator==(const TicTacToe& other) const {
    return n == other.n && board == other.board;
}

bool TicTacToe::operator!=(const TicTacToe& other) const {
    return !(*this == other);
}

// Indexed access.

TicTacToe::Row TicTacToe::operator[](std::size_t row) {
    return Row(board.at(row));
}

TicTacToe::ConstRow TicTacToe::operator[](
    std::size_t row) const {
    return ConstRow(board.at(row));
}

// Board operations.

std::size_t TicTacToe::size() const {
    return n;
}

bool TicTacToe::canPlace(
    std::size_t row, std::size_t column) const {
    return row < n && column < n &&
           board[row][column] == ' ';
}

char TicTacToe::operator()(
    std::size_t row, std::size_t column) const {
    if (row >= n || column >= n) {
        return ' ';
    }

    return board[row][column];
}

void TicTacToe::set(
    std::size_t row, std::size_t column, char mark) {
    if (canPlace(row, column) &&
        (mark == 'X' || mark == 'O')) {
        board[row][column] = mark;
    }
}

// Winner detection.

bool TicTacToe::checkRow(
    std::size_t row, char& winner) const {
    const char first = board[row][0];

    if (first == ' ') {
        return false;
    }

    for (std::size_t column = 1; column < n; ++column) {
        if (board[row][column] != first) {
            return false;
        }
    }

    winner = first;
    return true;
}

bool TicTacToe::checkCol(
    std::size_t column, char& winner) const {
    const char first = board[0][column];

    if (first == ' ') {
        return false;
    }

    for (std::size_t row = 1; row < n; ++row) {
        if (board[row][column] != first) {
            return false;
        }
    }

    winner = first;
    return true;
}

bool TicTacToe::checkMainDiag(char& winner) const {
    const char first = board[0][0];

    if (first == ' ') {
        return false;
    }

    for (std::size_t i = 1; i < n; ++i) {
        if (board[i][i] != first) {
            return false;
        }
    }

    winner = first;
    return true;
}

bool TicTacToe::checkAntiDiag(char& winner) const {
    const char first = board[0][n - 1];

    if (first == ' ') {
        return false;
    }

    for (std::size_t i = 1; i < n; ++i) {
        if (board[i][n - 1 - i] != first) {
            return false;
        }
    }

    winner = first;
    return true;
}

char TicTacToe::checkWinner() const {
    char winner = ' ';

    for (std::size_t row = 0; row < n; ++row) {
        if (checkRow(row, winner)) {
            return winner;
        }
    }

    for (std::size_t column = 0; column < n; ++column) {
        if (checkCol(column, winner)) {
            return winner;
        }
    }

    if (checkMainDiag(winner)) {
        return winner;
    }

    if (checkAntiDiag(winner)) {
        return winner;
    }

    return ' ';
}

// Board state operations.

bool TicTacToe::isFull() const {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;
            }
        }
    }

    return true;
}

void TicTacToe::reset() {
    for (auto& row : board) {
        for (char& cell : row) {
            cell = ' ';
        }
    }
}

// Stream output.

std::ostream& operator<<(
    std::ostream& os, const TicTacToe& game) {
    os << game.n << '\n';

    for (const auto& row : game.board) {
        for (char cell : row) {
            os << (cell == ' ' ? '.' : cell);
        }

        os << '\n';
    }

    return os;
}

// Stream input.

std::istream& operator>>(
    std::istream& is, TicTacToe& game) {
    std::size_t size;

    if (!(is >> size)) {
        return is;
    }

    if (size == 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::vector<std::vector<char>> newBoard(
        size, std::vector<char>(size, ' '));

    for (std::size_t row = 0; row < size; ++row) {
        for (std::size_t column = 0; column < size; ++column) {
            char cell;

            if (!(is >> cell)) {
                return is;
            }

            if (cell == '.') {
                newBoard[row][column] = ' ';
            } else if (cell == 'X' || cell == 'O') {
                newBoard[row][column] = cell;
            } else {
                is.setstate(std::ios::failbit);
                return is;
            }
        }
    }

    game.n = size;
    game.board = std::move(newBoard);

    return is;
}
