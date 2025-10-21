/**
 * Main.cpp
 * CSE 332S
 * Lab Num: 3
 * Author: Qiyuan Huang
*/
#include "TicTacToeGame.h"
#include <iostream>
#include <string>

static int usage(const char* prog) {
    std::cerr << "Usage: " << prog << " TicTacToe\n";
    return static_cast<int>(ExitCode::BadUsage);
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) return usage(argv[0]);
        std::string arg = argv[1];
        if (arg != "TicTacToe") return usage(argv[0]);

        TicTacToeGame game;
        return game.play();
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << "\n";
        return static_cast<int>(ExitCode::TurnError);
    } catch (...) {
        std::cerr << "Unknown exception.\n";
        return static_cast<int>(ExitCode::TurnError);
    }
}
