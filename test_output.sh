#!/usr/bin/expect -f

# Compile the code
exec gcc -o chess_output main.c chessUtility.c pieceUtility.c -I./
puts "Compilation complete."
flush stdout

# Start the chess program
puts "Starting chess program..."
spawn ./chess_output
flush stdout

# Wait for the initial board output
expect {
    "R G B Q K B G R" {
        puts "Initial board detected."
        flush stdout

        # Simulate user moves
        send "move e2 e4\r"
        send "move e7 e5\r"
        send "exit\r"
    }
}

# Wait for the process to complete
expect eof
puts "Chess program finished."
flush stdout

# Capture output for comparison
set output [open "full_output.txt" "r"]
set contents [read $output]
close $output

# Extract initial board part from output
set actual_output [open "actual_output.txt" "w"]
puts $actual_output [lrange [split $contents "\n"] 0 23]
close $actual_output
puts "Initial board extracted."
flush stdout

# Create expected output
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
puts "Expected output created."
flush stdout

# Compare outputs
if {[catch {exec diff -w actual_output.txt expected_output.txt} result]} {
    puts "Test Failed: Initial board output does not match expected"
    flush stdout
    exit 1
} else {
    puts "Board layout test passed!"
    flush stdout
}

# Check last line of output
set last_line [lindex [split $contents "\n"] end]
if {$last_line == "0" || $last_line == "1"} {
    puts "End check passed: Last line is $last_line."
    puts "All tests passed successfully."
    flush stdout
    exit 0
} else {
    puts "Test Failed: Last line is not 0 or 1, found '$last_line' instead."
    flush stdout
    exit 1
}
