// GomokuGame.cpp
#include "GomokuGame.h"
#include <iostream>
#include <iomanip>

GomokuGame::GomokuGame()
    : GameBase(19, 19, 5) {  // 19x19, 连 5 个
    current_player = "B";    // 黑先
    max_display_len = 2;     // 为了容纳 "19"
}

void GomokuGame::print() {
    std::cout << *this << std::endl;
}

std::ostream & operator<<(std::ostream &os, const GomokuGame &g) {
    using std::setw;
    std::size_t w = g.max_display_len + 1;

    for (int row = g.height - 1; row >= 0; --row) {
        os << setw(w) << (row + 1);
        for (unsigned col = 0; col < g.width; ++col) {
            std::string p = g.piece_at(col, row);
            if (p == " ") p = ".";
            os << setw(w) << p;
        }
        os << "\n";
    }

    os << setw(w) << "X";
    for (unsigned col = 0; col < g.width; ++col) {
        os << setw(w) << (col + 1);
    }
    return os;
}

bool GomokuGame::check_line(unsigned x, unsigned y, int dx, int dy) const {
    std::string p = piece_at(x, y);
    if (p == " ") return false;

    for (unsigned k = 1; k < win_length; ++k) {
        int nx = int(x) + dx * int(k);
        int ny = int(y) + dy * int(k);
        if (nx < 0 || ny < 0 ||
            nx >= int(width) || ny >= int(height)) {
            return false;
        }
        if (piece_at(nx, ny) != p) return false;
    }
    return true;
}

bool GomokuGame::done() {
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            if (piece_at(x, y) != " ") {
                if (check_line(x, y, 1, 0)  ||  // →
                    check_line(x, y, 0, 1)  ||  // ↑
                    check_line(x, y, 1, 1)  ||  // ↗
                    check_line(x, y, 1,-1)) {   // ↘
                    return true;
                }
            }
        }
    }
    return false;
}

bool GomokuGame::draw() {
    if (done()) return false;
    for (const auto &p : board)
        if (p == " ") return false;
    return true;
}

int GomokuGame::turn() {
    unsigned x, y;
    int r;
    do {
        r = prompt(x, y);
        if (r == quit_game) return quit_game;
    } while (r != success);

    place_piece(x, y, current_player);

    print();
    std::cout << "Player " << current_player
              << " played at (" << x + 1 << "," << y + 1 << ")\n";

    current_player = (current_player == "B" ? "W": "B");
    return success;
}
