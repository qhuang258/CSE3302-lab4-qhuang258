/**
* Main.cpp
 * CSE 332S
 * Lab Num: 4
 * Author: Qiyuan Huang
*/

#include "GameBase.h"
#include <iostream>
#include <memory>

static int usage(const char* prog) {
    std::cerr << "Usage: " << prog << " TicTacToe | Gomoku\n";
    return input_error;
}

int main(int argc, char* argv[]) {
    try {
        GameBase * raw = GameBase::instance(argc, argv);
        if (!raw) return usage(argv[0]);

        std::shared_ptr<GameBase> game(raw);
        return game->play();
    }
    catch (...) {
        std::cerr << "Unexpected exception.\n";
        return bad_alloc_error;
    }
}
