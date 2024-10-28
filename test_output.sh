#!/bin/bash

# Compile the code
gcc -o chess_output main.c chessUtility.c pieceUtility.c -I./

# Run the program and capture the output
./chess_output > actual_output.txt

# Expected output for the initial board (types)
cat << EOF > expected_board_output.txt
R G B Q K B G R
P P P P P P P P
X X X X X X X X
X X X X X X X X
X X X X X X X X
X X X X X X X X
P P P P P P P P
R G B Q K B G R
EOF

# Expected output for sides
cat << EOF > expected_sides_output.txt
O O O O O O O O
O O O O O O O O
X X X X X X X X
X X X X X X X X
X X X X X X X X
X X X X X X X X
P P P P P P P P
P P P P P P P P
EOF

# Expected output for highlights (assuming default 0 for all)
cat << EOF > expected_highlights_output.txt
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
EOF

# Separate the output sections
awk '/^[A-Za-z]/{print > "actual_board_output.txt"} /^[OPX]/{print > "actual_sides_output.txt"} /^[01]/{print > "actual_highlights_output.txt"}' actual_output.txt

# Compare each output section to the expected output
diff -w actual_board_output.txt expected_board_output.txt > /dev/null
board_result=$?

diff -w actual_sides_output.txt expected_sides_output.txt > /dev/null
sides_result=$?

diff -w actual_highlights_output.txt expected_highlights_output.txt > /dev/null
