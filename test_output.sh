#!/usr/bin/expect -f

# Compile the code
set compile_result [exec gcc -o chess_output main.c chessUtility.c pieceUtility.c -I./]
if {$compile_result != ""} {
    puts "Compilation failed: $compile_result"
    exit 1
}
puts "Compilation succeeded."

# Start the chess program
puts "Starting chess program..."
spawn ./chess_output

# Wait for the initial board output
expect {
    "R G B Q K B G R" {
        puts "Initial board detected."

        # Test valid move scenario (e.g., moving a pawn)
        send "move e2 e4\r"
        expect "Where would you like to move this piece?"
        send "3\r"          # Row input for e4 (3 based on your row indexing)
        send "e\r"          # Column input for e4
        expect {
            "Check!" {
                puts "Valid move test passed."
            }
            "Invalid move, please try again" {
                puts "Valid move test failed. Unexpected output."
                exit 1
            }
            default {
                puts "Unexpected output after moving: $expect_out(buffer)"
                exit 1
            }
        }
    }
}

# Wait for the process to complete
expect eof
puts "Chess program finished."

# Capture output for comparison
set output [open "full_output.txt" "r"]
set contents [read $output]
close $output

# Extract the initial board part from the output
set actual_output [open "actual_output.txt" "w"]
puts $actual_output [lrange [split $contents "\n"] 0 23]
close $actual_output

# Expected output file for comparison
set expected_output [open "expected_output.txt" "w"]
puts $expected_output {
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
}
close $expected_output

# Compare the initial board output to expected output
if {[catch {exec diff -w actual_output.txt expected_output.txt} result]} {
    puts "Test Failed: Initial board output does not match expected"
    puts "Actual Initial Output:"
    set actual_output [open "actual_output.txt" "r"]
    puts [read actual_output]
    close actual_output
    puts "Expected Initial Output:"
    set expected_output [open "expected_output.txt" "r"]
    puts [read expected_output]
    close expected_output
    exit 1
} else {
    puts "Board layout test passed!"
}

# Check if the last line of the full output is 0 or 1
set last_line [lindex [split $contents "\n"] end]
if {$last_line == "0" || $last_line == "1"} {
    puts "End check passed: Last line is $last_line."
    exit 0
} else {
    puts "Test Failed: Last line is not 0 or 1, found '$last_line' instead."
    exit 1
}

# Additional tests for invalid moves
puts "Running additional tests for invalid moves..."
spawn ./chess_output
expect {
    "R G B Q K B G R" {
        # Test invalid move scenario (e.g., moving a pawn to an occupied square)
        send "move e2 e4\r"
        expect "Where would you like to move this piece?"
        send "3\r"          # Row input for e4 (3 based on your row indexing)
        send "d\r"          # Invalid move input to d4 (occupied by pawn)
        expect "Invalid move, please try again" # Expecting output for invalid move
        puts "Invalid move test passed."
        expect eof
    }
}

puts "All tests completed."
