#!/bin/bash

# The script creates a directory specified as the first
# parameter. Then it creates symbolic links to all files
# in the $PWD directory except the directory just created,
# if it's there.

FILECNT=1

[ $# -lt 1 ] && { echo "No directory specified!"; exit 1; }

mkdir -p $1
[ $? -ne 0 ] && { echo "Couldn't create the directory!"; exit 2; }

for file in $(ls -A); do
  [ "$file" = "$1" ] && continue
  ln -s ${PWD}/${file} ${1}/file${FILECNT}
  FILECNT=$(( FILECNT + 1 ))
done

