#pragma once
#include <vector>
#include <string>

enum result_code {
    success = 0,
    quit_game,
    draw_game,
    bad_alloc_error,
    input_error
};

class GameBase {
protected:
    unsigned int width, height, win_length;
    std::vector<std::string> board; // board[y * width + x]
    std::string current_player;
    std::size_t max_display_len;

    inline unsigned index(unsigned x, unsigned y) const {
        return y * width + x;
    }

public:
    GameBase(unsigned w, unsigned h, unsigned win);
    virtual ~GameBase() = default;

    virtual void print() = 0;
    virtual bool done() = 0;
    virtual bool draw() = 0;
    virtual int  turn() = 0;

    virtual int prompt(unsigned &x, unsigned &y);
    int play();

    std::string piece_at(unsigned x, unsigned y) const;
    void place_piece(unsigned x, unsigned y, const std::string &p);

    static GameBase * instance(int argc, char *argv[]);
};
