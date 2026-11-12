Design of Intelligent Systems Software — Lab 1

This repository contains my Lab 1 implementations in C++:

Single-variable polynomial class

Tic-Tac-Toe game (arbitrary board size)

Structure

lab1/polynomial/

Polynomial.h, Polynomial.cpp — class implementation

polynomial_cli.cpp — console menu to work with polynomials

polynomial_tests.cpp — simple test program

lab1/tictactoe/

TicTacToe.h, TicTacToe.cpp — game logic

tictactoe_cli.cpp — console game for two players

tictactoe_tests.cpp — simple test program

Build (plain g++)

From the polynomial folder:

g++ Polynomial.cpp polynomial_cli.cpp -o polynomial_app

g++ Polynomial.cpp polynomial_tests.cpp -o polynomial_tests

To compile and run polynomial application:

g++ -std=c++17 -Isrc src/Polynomial.cpp src/Polynomial_cli.cpp -o polynomial_app

./polynomial_app

To compile and run the polynomial tests:

g++ -std=c++17 -Isrc src/Polynomial.cpp tests/Polynomial_tests.cpp -o polynomial_tests

./polynomial_tests

To compile and run tictactoe application:

g++ -std=c++17 -Wall -Wextra -Wpedantic -Isrc src/TicTacToe.cpp src/TicTacToe_cli.cpp -o tictactoe_app

./tictactoe_app

To compile and run tictatctoe tests:

g++ -std=c++17 -Wall -Wextra -Wpedantic -Isrc src/TicTacToe.cpp tests/TicTacToe_tests.cpp -o tictactoe_tests

./tictactoe_tests