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
test "PINA: 0x00, state: LED1ON => PORTB: 0x01 "
setPINA 0x00
set state = LED1ON
continue 1
expectPORTB 0x01
expect state LED1ON
checkResult

test "PINA: 0x01, state: LED1ON => PORTB: 0x02 "
setPINA 0x01
set state = LED1ON
continue 1
expect state LED2ON
expectPortB 0x02
checkResult

test "PINA: 0x00, state: LED2N => PORTB: 0x02 "
setPINA 0x00
set state = LED2ON
continue 1
expectPORTB 0x02
expect state LED2ON
checkResult


test "PINA: 0x01, state: LED2N => PORTB: 0x01 "
setPINA 0x01
set state = LED2ON
continue 1
expectPORTB 0x01
expect state LED1ON
checkResult


test "PINA: 0x01, state: LED2N => PORTB: 0x01 "
setPINA 0x01
set state = LED2ON
continue 1
setPINA 0x00
continue 1
expectPORTB 0x01
expect state LED1ON
checkResult



test "PINA: 0x00, state: LED2N => PORTB: 0x01 "
setPINA 0x00
set state = LED2ON
continue 1
setPINA 0x01
continue 1
expectPORTB 0x01
expect state LED1ON
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
