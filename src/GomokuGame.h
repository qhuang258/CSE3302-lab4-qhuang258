// GomokuGame.h
#pragma once
#include "GameBase.h"
#include <ostream>

class GomokuGame : public GameBase {
public:
    GomokuGame();

    virtual void print() override;
    virtual bool done() override;
    virtual bool draw() override;
    virtual int  turn() override;

    friend std::ostream & operator<<(std::ostream &os, const GomokuGame &g);

private:
    bool check_line(unsigned int x, unsigned int y,
                    int dx, int dy) const;
};
