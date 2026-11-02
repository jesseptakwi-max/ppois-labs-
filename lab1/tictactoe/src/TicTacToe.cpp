#include "TicTacToe.h"

TicTacToe::TicTacToe(std::size_t size) 
: n(size), board(size, std::vector<char>(size, ' ')) {}

TicTacToe::TicTacToe(const TicTacToe& other) 
: n(other.n), board(other.board) {}

TicTacToe& TicTacToe::operator=(const TicTacToe& other) {
     if (this != &other) { 
        n = other.n; 
        board = other.board; } 
        return *this; 
    }

bool TicTacToe::operator==(const TicTacToe& other) const { 
    return n == other.n && board == other.board; 
}

bool TicTacToe::operator!=(const TicTacToe& other) const { 
    return !(*this == other); 
}

std::size_t TicTacToe::size() const { 
    return n; 
}

bool TicTacToe::canPlace(std::size_t r, std::size_t c) const { 
    return r < n && c < n && board[r][c] == ' '; 
}

char TicTacToe::operator()(std::size_t r, std::size_t c) const { 
    if (r >= n || c >= n) return ' '; 
    return board[r][c]; 
}

void TicTacToe::set(std::size_t r, std::size_t c, char mark) { 
    if (canPlace(r, c) && (mark == 'X' || mark == 'O')) { 
        board[r][c] = mark; } 
    }

bool TicTacToe::checkRow(std::size_t r, char& w) const { 
    char first = board[r][0]; 
    if (first == ' ') return false; 
    for (std::size_t c = 1; c < n; ++c) { 
        if (board[r][c] != first) return false;
     } 
     w = first; 
     return true; 
    }

bool TicTacToe::checkCol(std::size_t c, char& w) const { 
    char first = board[0][c]; 
    if (first == ' ') return false; 
    for (std::size_t r = 1; r < n; ++r) { 
        if (board[r][c] != first) return false; 
    } 
        w = first; 
        return true; 
    }

bool TicTacToe::checkMainDiag(char& w) const { 
    char first = board[0][0]; 
    if (first == ' ') return false; 
    for (std::size_t i = 1; i < n; ++i) { 
        if (board[i][i] != first) return false; 
    } 
        w = first; 
        return true; 
    }

bool TicTacToe::checkAntiDiag(char& w) const { 
    char first = board[0][n - 1]; 
    if (first == ' ') return false; 
    for (std::size_t i = 1; i < n; ++i) { 
        if (board[i][n - 1 - i] != first) return false; 
    } 
        w = first; 
        return true; 
    }

char TicTacToe::checkWinner() const { 
    char w = ' ';

    for (std::size_t r = 0; r < n; ++r)
    if (checkRow(r, w)) return w;


    for (std::size_t c = 0; c < n; ++c)
    if (checkCol(c, w)) return w;


    if (checkMainDiag(w)) return w;
    if (checkAntiDiag(w)) return w;

return ' ';
}

bool TicTacToe::isFull() const { 
    for (const auto& row : board) 
    for (char c : row) 
    if (c == ' ') return false; 
    return true; 
}

void TicTacToe::reset() { 
    for (auto& row : board) 
    for (char& c : row) 
    c = ' '; 
}

std::ostream& operator<<(std::ostream& os, const TicTacToe& g) { 
    os << g.n << "\n"; 
    for (const auto& row : g.board) { 
        for (char c : row) os << c;
         os << "\n"; 
        } 
        return os; 
    }

std::istream& operator>>(std::istream& is, TicTacToe& g) { 
    std::size_t size; 
    if (!(is >> size)){
        return is; 
    }

    g.n = size; 
    g.board.assign(size, std::vector<char>(size, ' ')); 
    for (std::size_t r = 0; r < size; ++r){
     for (std::size_t c = 0; c < size; ++c) {
     if(!( is >> g.board[r][c])){
     return is;
     }
    }
}
     
    return is;
}