# PPOIS Labs

C++ coursework projects for the PPOIS laboratory assignments.

## Lab 1

Lab 1 contains two independent C++17 console applications:

1. **Polynomial** – a single-variable polynomial implementation with arithmetic operations.
2. **Tic-Tac-Toe** – a configurable Tic-Tac-Toe game with a console interface.

Each project has its own source code, command-line interface, and unit tests.

## Project Structure

```text
PPOIS Labs/
├── .github/
│   └── workflows/
│       └── cpp-tests.yml
├── lab1/
│   ├── Polynomial/
│   │   ├── src/
│   │   │   ├── Polynomial.h
│   │   │   ├── Polynomial.cpp
│   │   │   └── Polynomial_cli.cpp
│   │   └── tests/
│   │       └── Polynomial_tests.cpp
│   └── tictactoe/
│       ├── src/
│       │   ├── TicTacToe.h
│       │   ├── TicTacToe.cpp
│       │   └── TicTacToe_cli.cpp
│       └── tests/
│           └── TicTacToe_tests.cpp
├── .gitignore
└── README.md
```

## Requirements

- C++17-compatible compiler (`g++` or `clang++`)
- [Catch2 v3](https://github.com/catchorg/Catch2) for unit testing
- [gcovr](https://gcovr.com/) for code coverage reports
- `clang-tidy` for static analysis
- Git

### Installing dependencies on macOS

Using Homebrew:

```bash
brew install catch2 gcovr
```

Check the installations:

```bash
g++ --version
gcovr --version
brew info catch2
```

## Polynomial

The Polynomial application implements single-variable polynomial operations.

### Features

- Create and store polynomials.
- Evaluate a polynomial at a given value of x.
- Add, subtract, and multiply polynomials.
- Divide polynomials.
- Access coefficients and determine polynomial degree.
- Compare polynomials.
- Read and display polynomials using stream operators.

### Build and run

Open a terminal in the repository root and run:

```bash
cd lab1/Polynomial
```

Compile the application:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Isrc \
src/Polynomial.cpp src/Polynomial_cli.cpp \
-o polynomial_app
```

Run:

```bash
./polynomial_app
```

### Run unit tests

Compile the tests with Catch2:

```bash
CATCH2_PREFIX="$(brew --prefix catch2)"

g++ -std=c++17 -Wall -Wextra -Wpedantic \
-I"$CATCH2_PREFIX/include" -Isrc \
src/Polynomial.cpp tests/Polynomial_tests.cpp \
-L"$CATCH2_PREFIX/lib" -lCatch2Main -lCatch2 \
-o polynomial_tests
```

Run the tests:

```bash
./polynomial_tests
```

### Measure code coverage

Compile the tests with coverage instrumentation:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic --coverage -O0 -g \
-I"$CATCH2_PREFIX/include" -Isrc \
src/Polynomial.cpp tests/Polynomial_tests.cpp \
-L"$CATCH2_PREFIX/lib" -lCatch2Main -lCatch2 \
-o polynomial_tests
```

Run the tests and generate the coverage report:

```bash
./polynomial_tests

gcovr --root . --filter 'src/Polynomial\.cpp$' --print-summary
```

## Tic-Tac-Toe

The Tic-Tac-Toe application implements a configurable console-based game.

### Features

- Start a new game.
- Choose the board size.
- Play using X and O.
- Validate player moves.
- Detect horizontal, vertical, and diagonal wins.
- Detect draws.
- Reset the game.
- Display game instructions.

### Build and run

From the repository root:

```bash
cd lab1/tictactoe
```

Compile the application:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Isrc \
src/TicTacToe.cpp src/TicTacToe_cli.cpp \
-o tictactoe_app
```

Run:

```bash
./tictactoe_app
```

### Run unit tests

Compile the tests with Catch2:

```bash
CATCH2_PREFIX="$(brew --prefix catch2)"

g++ -std=c++17 -Wall -Wextra -Wpedantic \
-I"$CATCH2_PREFIX/include" -Isrc \
src/TicTacToe.cpp tests/TicTacToe_tests.cpp \
-L"$CATCH2_PREFIX/lib" -lCatch2Main -lCatch2 \
-o tictactoe_tests
```

Run the tests:

```bash
./tictactoe_tests
```

### Measure code coverage

Compile the tests with coverage instrumentation:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic --coverage -O0 -g \
-I"$CATCH2_PREFIX/include" -Isrc \
src/TicTacToe.cpp tests/TicTacToe_tests.cpp \
-L"$CATCH2_PREFIX/lib" -lCatch2Main -lCatch2 \
-o tictactoe_tests
```

Run the tests and generate the coverage report:

```bash
./tictactoe_tests

gcovr --root . --filter 'src/TicTacToe\.cpp$' --print-summary
```

## Unit Testing

Both projects use Catch2 v3 for unit testing.

The test suites cover:

- Constructors and basic properties.
- Copy construction and assignment.
- Equality and inequality.
- Input and output stream operations.
- Valid and invalid inputs.
- Arithmetic operations and polynomial division.
- Tic-Tac-Toe moves, wins, draws, and board validation.

## Code Coverage

The project uses gcovr to measure line, function, and branch coverage.

The required line coverage threshold is **strictly greater than 90%** for each implementation file.

The GitHub Actions workflow checks coverage independently for:

- `Polynomial.cpp`
- `TicTacToe.cpp`

Latest verified local results:

| Project | Line coverage |
|---|---:|
| Polynomial | 92.0% |
| Tic-Tac-Toe | 99.3% |

## Continuous Integration

GitHub Actions automatically builds and checks both projects.

The workflow is located at:

```text
.github/workflows/cpp-tests.yml
```

It performs the following tasks:

1. Checks out the repository.
2. Installs Catch2, gcovr, and clang-tidy.
3. Compiles both applications.
4. Compiles and runs both unit test suites.
5. Checks that line coverage is strictly above 90%.
6. Performs static analysis using clang-tidy.
7. Packages both applications when a version tag is pushed.

The workflow runs on pushes to the configured branches, pull requests targeting `main`, and manual dispatches.

## Technologies

- C++17
- Catch2 v3
- GCC / Clang
- gcov / gcovr
- clang-tidy
- Git and GitHub Actions