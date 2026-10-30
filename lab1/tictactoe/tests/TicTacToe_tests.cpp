#include <cassert> 
#include "TicTacToe.h"

int main() { 
    TicTacToe g(3);

    assert(g.size() == 3);
    assert(g.checkWinner() == ' ');
    assert(!g.isFull());


    // X wins on first row
    g.set(0, 0, 'X');
    g.set(0, 1, 'X');
    g.set(0, 2, 'X');
    assert(g.checkWinner() == 'X');


    // Reset and test diagonal
    g.reset();
    g.set(0, 0, 'O');
    g.set(1, 1, 'O');
    g.set(2, 2, 'O');
    assert(g.checkWinner() == 'O');


    // Test canPlace
    assert(!g.canPlace(0, 0)); // already occupied
    assert(g.canPlace(0, 1));  // empty

    return 0;
}