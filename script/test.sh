#!/usr/bin/env sh

echo
echo "------------- Test -------------"
tune="0.038"
start=`date +%s.%N`
if command -v systemd-run &>/dev/null; then
  cat "a.inp" | systemd-run --scope -p MemoryMax=512M -q --user ./a.out
else
  cat "a.inp" | ./a.out
fi
end=`date +%s.%N`
dur=`echo "$end - $start - $tune" | bc`
echo
echo "Time: $(echo "($dur > 0) * $dur" | bc)s"
