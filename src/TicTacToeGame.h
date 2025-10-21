#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>

enum class ExitCode : int {
    SuccessWin = 0,
    UserQuit   = 1,
    Draw       = 2,
    BadUsage   = 3,
    TurnError  = 4
};

class TicTacToeGame {
    friend std::ostream& operator<<(std::ostream& os, const TicTacToeGame& g);

public:
    TicTacToeGame();
    bool done() const;                 // true if a 3-in-a-row is achieved (inner 3x3)
    bool draw() const;                 // true if no moves remain and not done()
    bool prompt(unsigned& x, unsigned& y);      // false if user typed "quit"
    int  turn();                       // performs exactly one valid move (or returns quit)
    int  play();                       // game loop, returns an ExitCode

private:
    static constexpr unsigned W = 5;
    static constexpr unsigned H = 5;

    // board[y][x], 0..4 with (0,0) at lower-left when printed
    std::vector<std::vector<char>> board_;
    char current_;                     // 'X' or 'O'
    unsigned turn_count_;              // number of *valid* moves made

    // track move history for printing: per-player list of "x, y"
    std::vector<std::string> x_moves_;
    std::vector<std::string> o_moves_;

    static bool inInner(unsigned x, unsigned y) { return (x >= 1 && x <= 3 && y >= 1 && y <= 3); }
    static bool emptyChar(char c) { return c == ' '; }

    bool placeIfValid(unsigned x, unsigned y);
    bool innerHasLine(char who) const; // helper for done()
    static void printMoves(std::ostream& os,
                           const std::vector<std::string>& xs,
                           const std::vector<std::string>& osMoves);
};

#ifndef CSE332LAB_TICTACTOEGAME_H
#define CSE332LAB_TICTACTOEGAME_H

#endif //CSE332LAB_TICTACTOEGAME_H