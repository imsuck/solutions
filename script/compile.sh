#!/usr/bin/env sh

# helix comment macro   "t\h;vghms`;a#<space><esc>"
# helix uncomment macro "ghlmd`dd"

DIR="$(dirname "$0")"

echo
echo "---------- Compilation ---------"
start=`date +%s.%N`
g++ -include bits/stdc++.h -include lib/debug.h -std=c++14 -DLOCAL \
-Wall -Wextra -Wconversion -Wshadow -Wfloat-equal -Wno-sign-conversion -Wno-sign-compare \
`# -O2` \
`# -fsanitize=undefined -fsanitize=address` \
-o a.out $(fd -Iae cpp --changed-within 3s)
end=`date +%s.%N`
echo "Compilation took: $(echo "$end - $start" | bc -l)s"

bash -c "$DIR/test.sh"
