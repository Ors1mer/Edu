#!/bin/sh

# The script writes '@' amount_of_files_in_the_directory times

for f in $(ls -A); do
  printf '@'
done
echo

