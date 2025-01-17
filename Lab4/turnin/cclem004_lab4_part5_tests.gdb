# Test file for "Lab4"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:

# Add tests below
test "PINA: 0x00, state: WAIT => PORTB: 0x00 "
setPINA 0x00
set state = WAIT
continue 1
expectPORTB 0x00
expect state WAIT
checkResult


test "PINA: 0x04, state: WAIT => PORTC: 0x00 "
setPINA 0x04
set state = WAIT
continue 1
expectPORTB 0x00
expect state FIRSTBUTTON
checkResult

test "PINA: 0x04, PINA 0x02 state: WAIT => PORTC: 0x06 "
setPINA 0x04
set state = WAIT
continue 1
setPINA 0x00
continue 1
setPINB 0x02
continue 1
expect state SECONDBUTTON
expectPORTB 0x00
checkResult

test "unlock after lock"
setPINA 0x80
set state = WAIT
continue 2
setPINA 0x04
continue 2
setPINA 0x00
continue 1
setPINA 0x01
continue 2
setPINA 0x00
continue 1
setPINA 0x02
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
expect i 3
expect state UNLOCK
expectPORTB 0x01

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
