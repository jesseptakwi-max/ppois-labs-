#include "TicTacToe.h"

#include <cassert>
#include <sstream>

int main() {
    TicTacToe game(3);
    assert(game.size() == 3);
    assert(game.checkWinner() == ' ');
    assert(!game.isFull());
    assert(game.canPlace(0, 0));
    assert(!game.canPlace(3, 0));
    assert(!game.canPlace(0, 3));
    assert(game(3, 0) == ' ');

    game.set(0, 0, 'X');
    game.set(0, 1, 'X');
    game.set(0, 2, 'X');
    assert(game.checkWinner() == 'X');
    assert(!game.canPlace(0, 0));
    game.set(1, 1, 'Z'); // invalid marks are ignored
    assert(game(1, 1) == ' ');

    game.reset();
    assert(game.checkWinner() == ' ');
    game.set(0, 0, 'O');
    game.set(1, 0, 'O');
    game.set(2, 0, 'O');
    assert(game.checkWinner() == 'O'); // column

    game.reset();
    game.set(0, 0, 'X');
    game.set(1, 1, 'X');
    game.set(2, 2, 'X');
    assert(game.checkWinner() == 'X'); // main diagonal

    game.reset();
    game.set(0, 2, 'O');
    game.set(1, 1, 'O');
    game.set(2, 0, 'O');
    assert(game.checkWinner() == 'O'); // anti-diagonal

    game.reset();
    game.set(0, 0, 'X');
    TicTacToe copied(game);
    assert(copied == game);
    TicTacToe assigned(2);
    assigned = game;
    assert(assigned == game);
    TicTacToe* sameObject = &assigned;
    assigned = *sameObject;
    assert(assigned == game);
    assert(assigned != TicTacToe(2));

    TicTacToe full(2);
    full.set(0, 0, 'X');
    full.set(0, 1, 'O');
    full.set(1, 0, 'O');
    full.set(1, 1, 'X');
    assert(full.isFull());
    assert(full.checkWinner() == 'X');
    full.reset();
    assert(!full.isFull());

    std::stringstream serialized;
    serialized << game;
    TicTacToe restored(1);
    serialized >> restored;
    assert(restored == game);

    std::stringstream invalidInput("not-a-size");
    invalidInput >> restored;
    assert(invalidInput.fail());

    return 0;
}
