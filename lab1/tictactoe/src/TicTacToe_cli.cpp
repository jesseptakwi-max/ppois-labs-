#include <iostream> 
#include "TicTacToe.h"

void printBoard(const TicTacToe& g) { 
    std::size_t n = g.size(); 
    std::cout << "\n"; 
    for (std::size_t r = 0; r < n; ++r) { 
        for (std::size_t c = 0; c < n; ++c) { 
            char ch = g(r, c); 
            if (ch == ' ') ch = '.'; 
            std::cout << ch; 
            if (c + 1 < n) std::cout << " | "; 
        } 
        std::cout << "\n"; 
        if (r + 1 < n) {
             for (std::size_t c = 0; c < n; ++c) { 
                std::cout << "--"; 
                if (c + 1 < n) std::cout << "+"; 
            } 
            std::cout << "\n"; 
        }
     }
      std::cout << "\n"; 
    }

int main() { 
    std::size_t n;
     std::cout << "Board size (e.g. 3): "; 
     std::cin >> n; 
     if (!std::cin || n < 2) { 
        std::cout << "Invalid size, using 3.\n";
         n = 3; 
    }


    TicTacToe game(n);
    char player = 'X';


    while (true) {
        printBoard(game);

    
        char w = game.checkWinner();
        if (w != ' ') {
        
            std::cout << "Player " << w << " wins!\n";
            break;
        }
    
        if (game.isFull()) {
        
            std::cout << "It's a draw.\n";
            break;
        }

    
        std::size_t r, c;
        std::cout << "Player " << player << " enter row and column (0-based): ";
        std::cin >> r >> c;
        if (!std::cin) {
            std::cout << "Invalid input, exiting.\n";
            break;
        }

    
        if (!game.canPlace(r, c)) {
            std::cout << "Cannot place there, try again.\n";
            continue;
        }

    
        game.set(r, c, player);
        player = (player == 'X') ? 'O' : 'X';
    }


    std::cout << "Final board:\n";
    printBoard(game);
    std::cout << "Game over.\n";

    return 0;
}