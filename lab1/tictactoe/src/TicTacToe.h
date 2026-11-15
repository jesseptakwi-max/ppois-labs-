/**
 * @file TicTacToe.h
 * @brief Declaration of the TicTacToe class.
 *
 * Defines a configurable square Tic-Tac-Toe board and
 * its game operations.
 */

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <iostream>

/**
 * @brief Represents a Tic-Tac-Toe game board of configurable size.
 *
 * Stores an n x n board and provides operations for placing marks,
 * detecting a winner, checking whether the board is full, and
 * stream input/output.
 */
class TicTacToe {
public:
    /**
     * @brief Creates an empty square board.
     * @param size Side length of the board (default 3).
     */
    explicit TicTacToe(std::size_t size = 3);

    /**
     * @brief Copy constructor.
     * @param other Game to copy.
     */
    TicTacToe(const TicTacToe& other);

    /**
     * @brief Copy assignment operator.
     * @param other Game to copy.
     * @return Reference to this game.
     */
    TicTacToe& operator=(const TicTacToe& other);

    /**
     * @brief Checks whether two boards are equal.
     * @param other Game to compare with.
     * @return true if the boards are equal, otherwise false.
     */
    bool operator==(const TicTacToe& other) const;

    /**
     * @brief Checks whether two boards are different.
     * @param other Game to compare with.
     * @return true if the boards differ, otherwise false.
     */
    bool operator!=(const TicTacToe& other) const;

    /**
     * @brief Gets the side length of the board.
     * @return Board size.
     */
    std::size_t size() const;

    /**
     * @brief Checks whether a mark can be placed in a cell.
     * @param r Row index.
     * @param c Column index.
     * @return true if the cell is available, otherwise false.
     */
    bool canPlace(std::size_t r, std::size_t c) const;

    /**
     * @brief Gets the content of a cell.
     * @param r Row index.
     * @param c Column index.
     * @return Character stored in the cell.
     */
    char operator()(std::size_t r, std::size_t c) const;

    /**
     * @brief Places a mark in a cell.
     * @param r Row index.
     * @param c Column index.
     * @param mark Mark to place ('X' or 'O').
     *
     * Invalid coordinates, occupied cells and invalid marks
     * are ignored.
     */
    void set(std::size_t r, std::size_t c, char mark);

    /**
     * @brief Determines the winner of the game.
     * @return 'X' or 'O' if a player has won, or a space
     * character if there is no winner.
     */
    char checkWinner() const;

    /**
     * @brief Checks whether the board has no free cells.
     * @return true if the board is full, otherwise false.
     */
    bool isFull() const;

    /**
     * @brief Clears the board so a new game can start.
     *
     * The board dimensions remain unchanged.
     */
    void reset();

    /**
     * @brief Writes the board to an output stream.
     * @param os Output stream.
     * @param g Game to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const TicTacToe& g);

    /**
     * @brief Reads a board from an input stream.
     * @param is Input stream.
     * @param g Game to populate.
     * @return Reference to the input stream.
     */
    friend std::istream& operator>>(std::istream& is, TicTacToe& g);

private:
    /// Side length of the board.
    std::size_t n;

    /// Grid containing the board's cell contents.
    std::vector<std::vector<char>> board;

    /**
     * @brief Checks a row for a winning line.
     * @param r Row index.
     * @param[out] w Receives the winning mark if the row is won.
     * @return true if the row contains a winning line.
     */
    bool checkRow(std::size_t r, char& w) const;

    /**
     * @brief Checks a column for a winning line.
     * @param c Column index.
     * @param[out] w Receives the winning mark if the column is won.
     * @return true if the column contains a winning line.
     */
    bool checkCol(std::size_t c, char& w) const;

    /**
     * @brief Checks the main diagonal for a winning line.
     * @param[out] w Receives the winning mark if the diagonal is won.
     * @return true if the main diagonal contains a winning line.
     */
    bool checkMainDiag(char& w) const;

    /**
     * @brief Checks the anti-diagonal for a winning line.
     * @param[out] w Receives the winning mark if the diagonal is won.
     * @return true if the anti-diagonal contains a winning line.
     */
    bool checkAntiDiag(char& w) const;
};

#endif // TICTACTOE_H
