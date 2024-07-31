#!/usr/bin/env bash

# helix comment macro   "t\h;vghms`;a#<space><esc>"
# helix uncomment macro "ghlmd`dd"

DIR="$(dirname "$0")"

echo
echo "---------- Compilation ---------"
start=`date +%s.%N`
g++ -include bits/stdc++.h -include lib/debug.h -std=c++14 -DLOCAL \
-Wall -Wextra -Wconversion -Wshadow -Wfloat-equal -Wno-sign-conversion -Wno-sign-compare \
`# -O2` \
-fsanitize=undefined -fsanitize=address -g \
-o a.out $(fd -Iae cpp --changed-within 3s)
ok=$?
end=`date +%s.%N`
echo "Compilation took: $(echo "$end - $start" | bc -l)s"

if [[ $ok == 0 ]]; then
bash -c "$DIR/test.sh"
fi
