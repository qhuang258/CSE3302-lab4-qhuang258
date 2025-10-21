#include "TicTacToeGame.h"
#include <sstream>
#include <iomanip>
#include <cctype>

TicTacToeGame::TicTacToeGame()
: board_(H, std::vector<char>(W, ' ')), current_('X'), turn_count_(0) {
    // Outer ring stays empty (already ' '); inner 3x3 starts empty and accepts moves.
}

std::ostream& operator<<(std::ostream& os, const TicTacToeGame& g) {
    // Print from top row y=4 down to y=0; x=0..4 with axes
    for (int y = static_cast<int>(TicTacToeGame::H) - 1; y >= 0; --y) {
        os << std::setw(2) << y << " ";
        for (unsigned x = 0; x < TicTacToeGame::W; ++x) {
            os << (g.board_[y][x] == 'X' || g.board_[y][x] == 'O' ? g.board_[y][x] : ' ');
            if (x + 1 < TicTacToeGame::W) os << " ";
        }
        os << "\n";
    }
    os << "   ";
    for (unsigned x = 0; x < TicTacToeGame::W; ++x) os << " " << x;
    os << "\n";
    return os;
}

bool TicTacToeGame::innerHasLine(char who) const {
    // rows and cols within inner 1..3
    for (unsigned y = 1; y <= 3; ++y) {
        if (board_[y][1] == who && board_[y][2] == who && board_[y][3] == who) return true;
    }
    for (unsigned x = 1; x <= 3; ++x) {
        if (board_[1][x] == who && board_[2][x] == who && board_[3][x] == who) return true;
    }
    // diagonals within inner
    if (board_[1][1] == who && board_[2][2] == who && board_[3][3] == who) return true;
    if (board_[1][3] == who && board_[2][2] == who && board_[3][1] == who) return true;
    return false;
}

bool TicTacToeGame::done() const {
    return innerHasLine('X') || innerHasLine('O');
}

bool TicTacToeGame::draw() const {
    if (done()) return false;
    // no remaining moves in inner 3x3?
    for (unsigned y = 1; y <= 3; ++y)
        for (unsigned x = 1; x <= 3; ++x)
            if (emptyChar(board_[y][x])) return false;
    return true;
}

bool TicTacToeGame::placeIfValid(unsigned x, unsigned y) {
    if (!inInner(x, y)) return false;
    if (!emptyChar(board_[y][x])) return false;
    board_[y][x] = current_;
    return true;
}

bool TicTacToeGame::prompt(unsigned& x, unsigned& y) {
    while (true) {
        std::cout << "Enter \"x,y\" for your move in 1..3,1..3 or \"quit\": ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "\nInput stream closed. Treating as quit.\n";
            return false;
        }
        // trim spaces
        while (!line.empty() && std::isspace(static_cast<unsigned char>(line.back()))) line.pop_back();
        size_t start = 0;
        while (start < line.size() && std::isspace(static_cast<unsigned char>(line[start]))) ++start;
        if (start > 0) line = line.substr(start);

        if (line == "quit") return false;

        // replace one comma with space and parse
        auto comma = line.find(',');
        if (comma != std::string::npos) {
            line[comma] = ' ';
            std::istringstream iss(line);
            unsigned xi, yi;
            if (iss >> xi >> yi) {
                x = xi; y = yi;
                return true;
            }
        }
        std::cout << "Bad input. Please enter like \"2,3\" or \"quit\".\n";
    }
}

static std::string coordStr(unsigned x, unsigned y) {
    std::ostringstream oss; oss << x << ", " << y; return oss.str();
}

void TicTacToeGame::printMoves(std::ostream& os,
                               const std::vector<std::string>& xs,
                               const std::vector<std::string>& osMoves) {
    os << "\n";
    os << "Player X: ";
    for (size_t i = 0; i < xs.size(); ++i) {
        if (i) os << "; ";
        os << xs[i];
    }
    os << "\n";
    os << "Player O: ";
    for (size_t i = 0; i < osMoves.size(); ++i) {
        if (i) os << "; ";
        os << osMoves[i];
    }
    os << "\n";
}

int TicTacToeGame::turn() {
    std::cout << "Player " << current_ << "'s turn.\n";
    unsigned x=0, y=0;
    while (true) {
        if (!prompt(x, y)) {
            std::cout << "User requested to quit.\n";
            return static_cast<int>(ExitCode::UserQuit);
        }
        if (placeIfValid(x, y)) {
            // record, print, swap turn
            if (current_ == 'X') x_moves_.push_back(coordStr(x, y));
            else                 o_moves_.push_back(coordStr(x, y));

            ++turn_count_;
            std::cout << *this;
            printMoves(std::cout, x_moves_, o_moves_);
            current_ = (current_ == 'X' ? 'O' : 'X');
            return 0; // one valid move made
        } else {
            std::cout << "Invalid move. Use inner squares (1..3,1..3) that are empty.\n";
        }
    }
}

int TicTacToeGame::play() {
    std::cout << *this; // initial board
    while (true) {
        int t = turn();
        if (t == static_cast<int>(ExitCode::UserQuit)) {
            std::cout << "Game ended: user quit after " << turn_count_ << " turn(s).\n";
            return static_cast<int>(ExitCode::UserQuit);
        }
        if (done()) {
            char winner = (current_ == 'X' ? 'O' : 'X'); // last mover
            std::cout << "Player " << winner << " wins in " << turn_count_ << " turn(s). Congrats!\n";
            return static_cast<int>(ExitCode::SuccessWin);
        }
        if (draw()) {
            std::cout << "Draw after " << turn_count_ << " turn(s): no winning moves remain.\n";
            return static_cast<int>(ExitCode::Draw);
        }
    }
}
