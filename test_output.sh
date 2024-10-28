#!/usr/bin/expect -f

# Compile the code
exec gcc -o chess_output main.c chessUtility.c pieceUtility.c -I./

# Start the chess program
spawn ./chess_output

# Wait for the initial board output
expect "R G B Q K B G R"
send_user "Sending command: move e2 e4\n"
send "move e2 e4\r"
expect "*"
send_user "Sending command: move e7 e5\n"
send "move e7 e5\r"
expect "*"
send_user "Sending command: exit\n"
send "exit\r"

# Wait for the process to complete
expect eof

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
exec diff -w actual_output.txt expected_output.txt
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
