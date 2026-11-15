
#include "TicTacToe.h"

#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <stdexcept>

TEST_CASE("TicTacToe construction and basic properties") {
    TicTacToe game(3);

    REQUIRE(game.size() == 3);
    REQUIRE(game.checkWinner() == ' ');
    REQUIRE_FALSE(game.isFull());
    REQUIRE(game.canPlace(0, 0));
    REQUIRE_FALSE(game.canPlace(3, 0));
    REQUIRE_FALSE(game.canPlace(0, 3));
    REQUIRE(game(3, 0) == ' ');

    REQUIRE_THROWS_AS(TicTacToe(0), std::invalid_argument);
}

TEST_CASE("TicTacToe placing marks and occupied cells") {
    TicTacToe game(3);

    game.set(0, 0, 'X');
    game.set(0, 1, 'X');
    game.set(0, 2, 'X');

    REQUIRE(game.checkWinner() == 'X');
    REQUIRE_FALSE(game.canPlace(0, 0));

    game.set(1, 1, 'Z');
    REQUIRE(game(1, 1) == ' ');
}

TEST_CASE("TicTacToe mutable and const indexing") {
    TicTacToe game(3);

    game[0][0] = 'X';
    game[0][1] = 'O';

    REQUIRE(game[0][0] == 'X');
    REQUIRE(game[0][1] == 'O');
    REQUIRE(game(0, 0) == 'X');

    const TicTacToe& constGame = game;

    REQUIRE(constGame[0][0] == 'X');
    REQUIRE(constGame[0][1] == 'O');
}

TEST_CASE("TicTacToe indexing rejects invalid positions") {
    TicTacToe game(3);

    REQUIRE_THROWS_AS(game[3][0], std::out_of_range);
    REQUIRE_THROWS_AS(game[0][3], std::out_of_range);
}

TEST_CASE("TicTacToe detects row winners") {
    TicTacToe game(3);

    game.set(0, 0, 'X');
    game.set(0, 1, 'X');
    game.set(0, 2, 'X');

    REQUIRE(game.checkWinner() == 'X');
}

TEST_CASE("TicTacToe detects column winners") {
    TicTacToe game(3);

    game.set(0, 0, 'O');
    game.set(1, 0, 'O');
    game.set(2, 0, 'O');

    REQUIRE(game.checkWinner() == 'O');
}

TEST_CASE("TicTacToe detects main diagonal winners") {
    TicTacToe game(3);

    game.set(0, 0, 'X');
    game.set(1, 1, 'X');
    game.set(2, 2, 'X');

    REQUIRE(game.checkWinner() == 'X');
}

TEST_CASE("TicTacToe detects anti-diagonal winners") {
    TicTacToe game(3);

    game.set(0, 2, 'O');
    game.set(1, 1, 'O');
    game.set(2, 0, 'O');

    REQUIRE(game.checkWinner() == 'O');
}

TEST_CASE("TicTacToe copying and assignment") {
    TicTacToe game(3);
    game.set(0, 0, 'X');

    TicTacToe copied(game);
    REQUIRE(copied == game);

    TicTacToe assigned(2);
    assigned = game;
    REQUIRE(assigned == game);

    TicTacToe* sameObject = &assigned;
    assigned = *sameObject;
    REQUIRE(assigned == game);

    REQUIRE(assigned != TicTacToe(2));
}

TEST_CASE("TicTacToe full board and reset") {
    TicTacToe full(2);

    full.set(0, 0, 'X');
    full.set(0, 1, 'O');
    full.set(1, 0, 'O');
    full.set(1, 1, 'X');

    REQUIRE(full.isFull());
    REQUIRE(full.checkWinner() == 'X');

    full.reset();

    REQUIRE_FALSE(full.isFull());
    REQUIRE(full.checkWinner() == ' ');
}

TEST_CASE("TicTacToe detects a draw") {
    TicTacToe draw(3);

    draw.set(0, 0, 'X');
    draw.set(0, 1, 'O');
    draw.set(0, 2, 'X');
    draw.set(1, 0, 'X');
    draw.set(1, 1, 'O');
    draw.set(1, 2, 'O');
    draw.set(2, 0, 'O');
    draw.set(2, 1, 'X');
    draw.set(2, 2, 'X');

    REQUIRE(draw.isFull());
    REQUIRE(draw.checkWinner() == ' ');
}

TEST_CASE("TicTacToe stream input and output") {
    TicTacToe game(3);
    game.set(0, 0, 'X');

    std::stringstream serialized;
    serialized << game;

    TicTacToe restored(1);
    serialized >> restored;

    REQUIRE(restored == game);
}

TEST_CASE("TicTacToe rejects incomplete input without changing the board") {
    TicTacToe unchanged(2);
    unchanged.set(0, 0, 'O');

    std::stringstream incomplete("2 X.");
    incomplete >> unchanged;

    REQUIRE(incomplete.fail());
    REQUIRE(unchanged.size() == 2);
    REQUIRE(unchanged[0][0] == 'O');
}

TEST_CASE("TicTacToe rejects invalid cell characters") {
    TicTacToe unchanged(2);
    unchanged.set(0, 0, 'O');

    std::stringstream invalidCell("2 XZ....");
    invalidCell >> unchanged;

    REQUIRE(invalidCell.fail());
    REQUIRE(unchanged[0][0] == 'O');
}

TEST_CASE("TicTacToe rejects invalid board sizes in stream input") {
    TicTacToe unchanged(2);

    std::stringstream invalidSize("0");
    invalidSize >> unchanged;

    REQUIRE(invalidSize.fail());
    REQUIRE(unchanged.size() == 2);
}
