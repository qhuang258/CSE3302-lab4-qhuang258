# CSE 332 Lab Base

Repository for submitting lab work

Note: We will read this file as raw text rather than markdown.

Name:Qiyuan Huang
Lab #: 4

Document your lab work here according to the lab specification

1. Overview

This project implements a framework that supports running multiple board games using inheritance and polymorphism.
The lab extends the previous TicTacToe game and introduces a second game: Gomoku (Five-in-a-Row), both of which inherit from a common abstract base class GameBase.

The program is invoked as:

./lab3-qhuang258 TicTacToe
./lab3-qhuang258 Gomoku

An invalid command prints usage information and terminates.

2. Design Decisions
   2.1 GameBase (Abstract Base Class)

The PDF requires consolidating shared functionality, so I designed GameBase to abstract common logic across games:

Shared board representation:
std::vector<std::string> board;
Each element of the vector represents a cell on the board, stored as a string (" ", "X", "O", "B", or "W").

Shared game loop:

play() handles turn progression.

Calls virtual functions turn(), done(), draw(), and print().

Shared prompting & input parsing:

prompt(unsigned& x, unsigned& y)
Handles "quit" and "x,y" input.
Also supports redirected input from a file (EOF treated as quit).

Shared coordinate validation is performed before any move is accepted.

This design avoids duplication and fits the lab requirement of using polymorphism.

2.2 TicTacToeGame

This game uses a 5×5 printed board with an inner 3×3 playable region (matches Lab 3 rules).
done() checks rows, columns, and diagonals in the 1–3 range.
draw() checks if all inner cells are filled and no winner exists.

Move history is stored and printed according to the Lab 3 specification.

2.3 GomokuGame

Gomoku required more design decisions:

Board Size

19×19 board using the same 1D vector as GameBase but accessed through helper functions.

Win Condition

Because win length varies across games, I stored:

win_length = 5

done() iterates through the entire board and for each non-empty cell checks four directions:

(1,0) horizontal

(0,1) vertical

(1,1) diagonal up-right

(1,-1) diagonal down-right

This satisfies the PDF requirement of directional checking.

Draw Condition

The PDF requires handling draw properly:

If done() is true → not draw
Else if any cell is " " → not draw
Else → draw

This is a conservative but correct implementation.

Player Representation

Black = "B" (first player)
White = "W"

3. Game Behavior

Both games support:

Entering moves using x,y format (1-based indexing)

Rejecting invalid or already occupied cells

Re-prompting after invalid input

"quit" to exit early

Displaying whose turn it is and where pieces were placed

Showing the board after every valid move

TicTacToe

Players alternate between 'X' and 'O'

Inner 3×3 grid determines game outcome

Prints move history after every turn

Gomoku

Players alternate between Black ("B") and White ("W")

A player wins by aligning 5 consecutive matching pieces

Full-board without a winner is a draw

1.  problem Code: if (check_line(x, y, 1, 0) &&
    check_line(x, y, 0, 1) &&
    check_line(x, y, 1, 1) &&
    check_line(x, y, 1, -1)) {
    return true;
    }
    return:Player B played at (10,10)
    B wins!

Problem: I wrote || to &&.

Fix:if (check_line(x, y, 1, 0) ||
check_line(x, y, 0, 1) ||
check_line(x, y, 1, 1) ||
check_line(x, y, 1,-1)) {
return true;
}

2. Problem code: piece_at(x, y) = current_player;

return: Segmentation fault: 11
reason: out of bound

Fix: Cif (x >= width || y >= height) {
std::cout << "Coordinates out of range.\n";
return prompt(x, y);
} 3. Problem code: place_piece(x, y, current_player);
problem: Player B played at (10,10)
Player W may also played at (10,10)
Fix:if (piece_at(x, y) != " ") {
std::cout << "Position occupied.\n";
return turn();
}
place_piece(x, y, current_player);

AI regulation: I asked AI about problem 2 which is the comilation failed. It says that there might be a out of bound error and I fixed it. 5. Testing Strategy

To satisfy the PDF’s “Testing” section, I tested in multiple ways:

Manual interactive testing

Normal move sequences

Winning horizontally, vertically, diagonally

Immediate quits

Illegal moves

Input redirection testing

Using a file containing moves:

./lab3-qhuang258 Gomoku < src/blah.txt

Test file includes both legal and illegal moves.

Boundary testing

Moves at edges (19,19), (1,19), etc.

Moves at corners

Diagonal wins starting at different positions

All tests behaved as expected.

6. Known Limitations

Gomoku draw detection is conservative (does not detect dead boards early).
This is acceptable according to the lab document.

The current design doesn’t include AI or strategic play (not required for this lab).

7. Collaboration Policy Statement

I completed this assignment independently.
I did not share code with other students.
Any discussions with classmates were limited to conceptual understanding and did not involve sharing code or solutions.
