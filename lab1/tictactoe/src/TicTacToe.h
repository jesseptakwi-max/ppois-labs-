#ifndef TICTACTOE_H 
#define TICTACTOE_H
#include <vector> 
#include <iostream>
class TicTacToe { 
    public: 
    explicit TicTacToe(std::size_t size = 3); 
    TicTacToe(const TicTacToe& other); 
    TicTacToe& operator=(const TicTacToe& other);

    bool operator==(const TicTacToe& other) const;
    bool operator!=(const TicTacToe& other) const;


    std::size_t size() const;
    bool canPlace(std::size_t r, std::size_t c) const;


    char operator()(std::size_t r, std::size_t c) const;
    void set(std::size_t r, std::size_t c, char mark);


    char checkWinner() const;
    bool isFull() const;
    void reset();


    friend std::ostream& operator<<(std::ostream& os, const TicTacToe& g);
    friend std::istream& operator>>(std::istream& is, TicTacToe& g);
    

private: 
    std::size_t n; 
    std::vector<std::vector<char>> board;


    bool checkRow(std::size_t r, char& w) const;
    bool checkCol(std::size_t c, char& w) const;
    bool checkMainDiag(char& w) const;
    bool checkAntiDiag(char& w) const;
};

#endif