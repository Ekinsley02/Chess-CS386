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
if diff -w actual_output.txt expected_output.txt > /dev/null; then
    echo "Test Passed!"
    exit 0
else
    echo "Test Failed: Output does not match expected"
    echo "Actual Output:"
    cat actual_output.txt
    echo "Expected Output:"
    cat expected_output.txt
    exit 1
fi
