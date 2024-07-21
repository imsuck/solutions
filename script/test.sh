#!/usr/bin/env sh

echo
echo "------------- Test -------------"
start=`date +%s.%N`
if command -v systemd-run &>/dev/null; then
  cat "a.inp" | systemd-run --scope -p MemoryMax=512M -q --user ./a.out
else
  cat "a.inp" | ./a.out
fi
end=`date +%s.%N`
echo
echo "Time: $(echo "$end - $start" | bc -l)s"
