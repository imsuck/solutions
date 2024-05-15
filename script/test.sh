#!/usr/bin/env sh

echo
echo "------------- Test -------------"
start=`date +%s.%N`
cat "a.inp" | ./a.out
end=`date +%s.%N`
echo
echo "Time: $(echo "$end - $start" | bc -l)s"
