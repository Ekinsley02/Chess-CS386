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
O O O O O O O O
O O O O O O O O
X X X X X X X X
X X X X X X X X
X X X X X X X X
X X X X X X X X
P P P P P P P P
P P P P P P P P
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
EOF

# Compare actual output to expected output
if diff -w actual_output.txt expected_output.txt > /dev/null; then
    echo "Board layout test passed!"
else
    echo "Test Failed: Output does not match expected"
    echo "Actual Output:"
    cat actual_output.txt
    echo "Expected Output:"
    cat expected_output.txt
    exit 1
fi

# Check if the last line of actual output is 0 or 1
last_line=$(tail -n 1 actual_output.txt)
if [[ "$last_line" == "0" || "$last_line" == "1" ]]; then
    echo "End check passed: Last line is $last_line."
    exit 0
else
    echo "Test Failed: Last line is not 0 or 1, found '$last_line' instead."
    exit 1
fi
