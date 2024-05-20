#!/bin/bash

# The script requires two numbers.
# The first one is the starting point, the second - the amount
# of numbers to be printed.

[ $# -lt 2 ] && { echo "Not enough parameters!"; exit 1; }

N=$1
M=$(( $2 + N ))

printf $N
N=$(( N + 1 ))
while [ $N -lt $M ]; do
  printf " $N"
  N=$(( N + 1 ))
done

echo

