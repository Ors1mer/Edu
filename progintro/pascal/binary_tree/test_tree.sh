#!/bin/sh

while read e1 e2 e3 e4 e5 e6 s ; do
  res=`./binary_tree $e1 $e2 $e3 $e4 $e5 $e6`;
  if [ x"$s" != x"$res" ]; then
    echo TEST $e1 $e2 $e3 $e4 $e5 $e6  FAILED: expected "$s", got "$res"
  fi
done <<END
  256 512 16 1024 32 128 1968
  432 -231 123 -56 76 -90 254
  1 2 3 4 5 6 21
END
