#!/bin/bash

# Compile the code
gcc -o chess_output main.c chessUtility.c pieceUtility.c -I./

# Run the program with a timeout and capture the output
timeout 10 ./chess_output > full_output.txt

# Check if the timeout was reached
if [ $? -eq 124 ]; then
    echo "Test Failed: Program timed out."
    exit 1
fi

# Extract the initial board part from the output
head -n 24 full_output.txt > actual_output.txt

# Expected output file for comparison
cat << EOF > expected_output.txt
# (expected output goes here)
EOF

# Compare the initial board output to expected output
if diff -w actual_output.txt expected_output.txt > /dev/null; then
    echo "Board layout test passed!"
else
    echo "Test Failed: Initial board output does not match expected"
    echo "Actual Initial Output:"
    cat actual_output.txt
    echo "Expected Initial Output:"
    cat expected_output.txt
    exit 1
fi

# Check if the last line of the full output is 0 or 1
last_line=$(tail -n 2 full_output.txt)
if [[ "$last_line" == "0" || "$last_line" == "1" ]]; then
    echo "End check passed: Last line is $last_line."
    exit 0
else
    echo "Test Failed: Last line is not 0 or 1, found '$last_line' instead."
    exit 1
fi
