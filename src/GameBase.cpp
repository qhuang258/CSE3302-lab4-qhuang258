// GameBase.cpp
#include "GameBase.h"
#include "TicTacToeGame.h"
#include "GomokuGame.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

GameBase::GameBase(unsigned int w, unsigned int h, unsigned int win)
    : width(w), height(h), win_length(win),
      board(w * h, " "), current_player(""), max_display_len(1) {}

std::string GameBase::piece_at(unsigned int x, unsigned int y) const {
    if (x >= width || y >= height) {
        return " ";
    }
    return board[index(x, y)];
}

void GameBase::place_piece(unsigned int x, unsigned int y, const std::string &p) {
    board[index(x, y)] = p;
    if (p.size() > max_display_len) {
        max_display_len = p.size();
    }
}

// 通用 prompt：读入 "<x,y>" 或 "quit"
int GameBase::prompt(unsigned int &x, unsigned int &y) {
    std::string line;
    std::cout << "Enter coordinates <x,y> or 'quit': ";
    if (!std::getline(std::cin, line)) {
        return input_error;
    }

    // 去掉前后空白
    auto trim = [](std::string &s) {
        while (!s.empty() && isspace(s.back())) s.pop_back();
        size_t i = 0;
        while (i < s.size() && isspace(s[i])) ++i;
        s = s.substr(i);
    };
    trim(line);

    if (line == "quit" || line == "QUIT" || line == "Quit") {
        return quit_game;
    }

    // 解析 x,y
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream iss(line);
    unsigned int px, py;
    if (!(iss >> px >> py)) {
        std::cout << "Invalid input, please use x,y format.\n";
        return input_error;
    }

    // 检查范围：注意这里假设 x, y 从 1 开始，到 width/height
    if (px < 1 || px > width || py < 1 || py > height) {
        std::cout << "Coordinates out of range.\n";
        return input_error;
    }

    // 检查位置是否为空
    if (piece_at(px - 1, py - 1) != " ") {
        std::cout << "That position is already occupied.\n";
        return input_error;
    }

    x = px - 1; // 内部用 0-based
    y = py - 1;
    return success;
}

int GameBase::play() {
    print();
    while (true) {
        if (done()) {
            std::cout << "Game over. " << current_player << " wins!\n";
            return success;
        }
        if (draw()) {
            std::cout << "Game is a draw.\n";
            return draw_game;
        }

        int r = turn();
        if (r == quit_game) {
            std::cout << "Player chose to quit.\n";
            return quit_game;
        } else if (r != success) {
            // 其他错误可以根据需要处理，这里简单提示
            std::cout << "Turn returned error code " << r << "\n";
        }
    }
}

// 工厂方法：根据 argv[1] 创建相应游戏
GameBase * GameBase::instance(int argc, char *argv[]) {
    if (argc < 2) {
        return nullptr;
    }
    std::string game_name = argv[1];
    if (game_name == "TicTacToe") {
        return new TicTacToeGame();
    } else if (game_name == "Gomoku") {
        return new GomokuGame();
    } else {
        return nullptr;
    }
}
