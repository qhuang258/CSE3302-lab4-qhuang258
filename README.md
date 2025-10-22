# CSE 332 Lab Base
Repository for submitting lab work

Note: We will read this file as raw text rather than markdown.

Name:Qiyuan Huang
Lab #: 3

Document your lab work here according to the lab specification
1.
Return Code: 1 (Compilation failed)
Problem: Compiler errors such as unknown type name 'constexpr' and a space is required between consecutive right angle brackets.
Fix: Delete the “Run Main.cpp” configuration and create a CMake Application configuration → select the target lab3-qhuang258. Now the compiler invokes clang++ --std=c++17 and the project builds successfully.
2. Problem: The program appears to hang on the input prompt and repeatedly prints
Bad input. Please enter like "2,3" or "quit", no matter what I type.
Fix: Clear and ignore the input stream when invalid input is detected:
std::cin.clear();
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
3. Problem: Entering 2,2 causes the program to terminate.
Fix: Read the entire line first and parse it safely:
std::string line;
   std::getline(std::cin, line);
   std::istringstream iss(line);
   char comma;
   if (!(iss >> x >> comma >> y) || comma != ',') {
   std::cout << "Invalid format.\n";
   }
4. Problem: After input 1,1, the piece appears in a different row than expected.
Cause: The board prints from top (y = 4) to bottom (y = 0), so visual orientation differs from the math style y-axis upwards.
Fix: Document that (0,0) is the bottom-left corner. Optionally invert print order if desired.
5. Probelm: Diagonal win not detected or wrongly detected on outer cells.
Reason: Loops or coordinate bounds using <= W instead of < W; includes border cells.
Fix: Make sure diagonal check uses inner indices only (1–3).
6. Problem: Input like 0,1 or 4,4 always returns “Invalid move.”
Root Cause: Design constraint — only inner 3×3 (1 ≤ x,y ≤ 3) is playable; outer ring is for labels only.
Fix: Not a defect; document this rule in README so testers don’t misinterpret it as a logic error.
7. Problem: When the last move creates a three-in-a-row, the game announces a win instead of a draw (even though no spaces remain).
Root Cause: The program checks done() before draw(), so a winning move takes precedence over a board-full state — same as standard Tic-Tac-Toe rules.
Fix: Clarify the evaluation order in documentation: each turn → check done() → if false, check draw(). No code change required.

AI regulation: I asked AI about problem 1 which is the comilation failed. It says that  CLion was building a single file (Main.cpp) instead of the CMake target, so the --std=c++17 flag was never applied and the compiler fell back to C++98.
Then I fixed it by deleting the “Run Main.cpp” configuration and creating a CMake Application configuration → select the target lab3-qhuang258. Now the compiler invokes clang++ --std=c++17 and the project builds successfully.