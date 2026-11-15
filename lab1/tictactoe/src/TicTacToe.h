
/**
 * @file TicTacToe.h
 * @brief Declaration of the TicTacToe class.
 *
 * Defines a configurable square Tic-Tac-Toe board and
 * its game operations.
 */

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <cstddef>
#include <iostream>
#include <vector>

/**
 * @brief Represents a configurable square Tic-Tac-Toe board.
 */
class TicTacToe {
public:
    /**
     * @brief Provides indexed access to a board row.
     */
    class Row {
    public:
        explicit Row(std::vector<char>& cells);

        char& operator[](std::size_t column);

    private:
        std::vector<char>& cells_;
    };

    /**
     * @brief Provides read-only indexed access to a board row.
     */
    class ConstRow {
    public:
        explicit ConstRow(const std::vector<char>& cells);

        const char& operator[](std::size_t column) const;

    private:
        const std::vector<char>& cells_;
    };

    /**
     * @brief Creates an empty square board.
     * @param size Side length of the board (default 3).
     */
    explicit TicTacToe(std::size_t size = 3);

    TicTacToe(const TicTacToe& other);
    TicTacToe& operator=(const TicTacToe& other);

    bool operator==(const TicTacToe& other) const;
    bool operator!=(const TicTacToe& other) const;

    /**
     * @brief Gets a modifiable board row.
     * @param row Row index.
     * @return Row proxy.
     */
    Row operator[](std::size_t row);

    /**
     * @brief Gets a read-only board row.
     * @param row Row index.
     * @return Constant row proxy.
     */
    ConstRow operator[](std::size_t row) const;

    std::size_t size() const;

    bool canPlace(std::size_t r, std::size_t c) const;

    char operator()(std::size_t r, std::size_t c) const;

    void set(std::size_t r, std::size_t c, char mark);

    char checkWinner() const;

    bool isFull() const;

    void reset();

    friend std::ostream& operator<<(
        std::ostream& os, const TicTacToe& game);

    friend std::istream& operator>>(
        std::istream& is, TicTacToe& game);

private:
    std::size_t n;
    std::vector<std::vector<char>> board;

    bool checkRow(std::size_t r, char& winner) const;
    bool checkCol(std::size_t c, char& winner) const;
    bool checkMainDiag(char& winner) const;
    bool checkAntiDiag(char& winner) const;
};

#endif // TICTACTOE_H
