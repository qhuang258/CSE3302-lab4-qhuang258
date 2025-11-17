# CSE 332 Lab Base
Repository for submitting lab work

Note: We will read this file as raw text rather than markdown.

Name:Qiyuan Huang
Lab #: 4

Document your lab work here according to the lab specification
1.
problem Code: if (check_line(x, y, 1, 0) &&
check_line(x, y, 0, 1) &&
check_line(x, y, 1, 1) &&
check_line(x, y, 1, -1)) {
return true;
}
return:Player B played at (10,10)
B wins!

Problem: I wrote || to &&.

Fix:if (check_line(x, y, 1, 0)  ||
check_line(x, y, 0, 1)  ||
check_line(x, y, 1, 1)  ||
check_line(x, y, 1,-1)) {
return true;
}

2. Problem code: piece_at(x, y) = current_player;

return: Segmentation fault: 11
reason: out of bound

Fix: Cif (x >= width || y >= height) {
std::cout << "Coordinates out of range.\n";
return prompt(x, y);
}
3. Problem code: place_piece(x, y, current_player); 
   problem: Player B played at (10,10)
   Player W may also played at (10,10)
Fix:if (piece_at(x, y) != " ") {
   std::cout << "Position occupied.\n";
   return turn();
   }
   place_piece(x, y, current_player);

AI regulation: I asked AI about problem 2 which is the comilation failed. It says that there might be a out of bound error and I fixed it.