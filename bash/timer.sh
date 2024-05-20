#!/bin/sh

# Launches the program & it's parameters that
# were specified as parameters for the script.
# After the program is executed, writes the number of seconds that passed.

[ $# -lt 1 ] && { echo "No program specified!"; exit 1; }

BEFORE=$(date +%s)
$*
RETURN=$?
AFTER=$(date +%s)
echo "Time passed: $(( AFTER - BEFORE )) sec"
exit $RETURN
