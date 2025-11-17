#include "TicTacToeGame.h"
#include <iostream>
#include <iomanip>

TicTacToeGame::TicTacToeGame()
    : GameBase(5, 5, 3) // width=5, height=5, win_length=3
{
    current_player = "X";   // GameBase field
}

void TicTacToeGame::print() {
    std::cout << *this << std::endl;
}

std::ostream & operator<<(std::ostream &os, const TicTacToeGame &g) {
    using std::setw;
    for (int y = g.height - 1; y >= 0; --y) {
        os << setw(2) << y << " ";
        for (unsigned x = 0; x < g.width; ++x) {
            std::string p = g.piece_at(x, y);
            if (p == " ") p = " ";
            os << p;
            if (x + 1 < g.width) os << " ";
        }
        os << "\n";
    }
    os << "   ";
    for (unsigned x = 0; x < g.width; ++x)
        os << " " << x;
    return os;
}

bool TicTacToeGame::innerHasLine(const std::string &p) const {
    for (unsigned y = 1; y <= 3; ++y)
        if (piece_at(1,y) == p && piece_at(2,y) == p && piece_at(3,y) == p) return true;

    for (unsigned x = 1; x <= 3; ++x)
        if (piece_at(x,1) == p && piece_at(x,2) == p && piece_at(x,3) == p) return true;

    return (piece_at(1,1)==p && piece_at(2,2)==p && piece_at(3,3)==p)
        || (piece_at(1,3)==p && piece_at(2,2)==p && piece_at(3,1)==p);
}

bool TicTacToeGame::done() {
    return innerHasLine("X") || innerHasLine("O");
}

bool TicTacToeGame::draw() {
    if (done()) return false;

    for (unsigned y = 1; y <= 3; ++y)
        for (unsigned x = 1; x <= 3; ++x)
            if (piece_at(x, y) == " ") return false;
    return true;
}

int TicTacToeGame::turn() {
    unsigned x=0,y=0;
    while (true) {
        int r = prompt(x, y);
        if (r == quit_game) return quit_game;

        if (piece_at(x,y) == " ") {
            place_piece(x, y, current_player);
            print();
            current_player = (current_player=="X" ? "O" : "X");
            return success;
        }
        std::cout << "Invalid move. Try again.\n";
    }
}
