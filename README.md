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
