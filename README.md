# PPOIS Labs

C++ Lab 1 contains two independent programs: Polynomial and Tic-Tac-Toe.

## Requirements

- C++17 compiler (for example, `g++`)
- `gcov`/`gcovr` for coverage reports
- `clang-tidy` for static analysis

## Polynomial

From `lab1/Polynomial`:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Isrc src/Polynomial.cpp src/Polynomial_cli.cpp -o polynomial_app
./polynomial_app

g++ -std=c++17 -Wall -Wextra -Wpedantic -Isrc src/Polynomial.cpp tests/Polynomial_tests.cpp -o polynomial_tests
./polynomial_tests
```

## Tic-Tac-Toe

From `lab1/tictactoe`:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Isrc src/TicTacToe.cpp src/TicTacToe_cli.cpp -o tictactoe_app
./tictactoe_app

g++ -std=c++17 -Wall -Wextra -Wpedantic -Isrc src/TicTacToe.cpp tests/TicTacToe_tests.cpp -o tictactoe_tests
./tictactoe_tests
```

The GitHub Actions workflow builds both CLIs, runs the unit tests, enforces more than 90% line coverage on each domain implementation, and runs `clang-tidy` static analysis. On a version tag (`v1.0.0`, for example), it packages the two CLI binaries into a downloadable Linux x86-64 release archive.
