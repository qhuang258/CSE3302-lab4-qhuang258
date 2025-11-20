#pragma once
#include "GameBase.h"
#include <vector>
#include <string>

class TicTacToeGame : public GameBase {
    friend std::ostream& operator<<(std::ostream& os, const TicTacToeGame& g);

public:
    TicTacToeGame();

    virtual void print() override;
    virtual bool done() override;
    virtual bool draw() override;
    virtual int  turn() override;

private:
    bool innerHasLine(const std::string &p) const;
};
