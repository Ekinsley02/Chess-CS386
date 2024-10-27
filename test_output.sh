#!/bin/bash

# Compile the code
gcc -o chess_output main.c chessUtility.c -I./

# Run the program and capture the output
./chess_output > actual_output.txt

# Expected output file for comparison
cat << EOF > expected_output.txt
R G B Q K B G R
P P P P P P P P
X X X X X X X X
X X X X X X X X
X X X X X X X X
X X X X X X X X
P P P P P P P P
R G B Q K B G R
EOF

# Compare actual output to expected output
if diff -q actual_output.txt expected_output.txt > /dev/null; then
    echo "Test Passed!"
    exit 0
else
    echo "Test Failed: Output does not match expected"
    exit 1
fi
