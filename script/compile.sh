#!/usr/bin/env bash

# helix comment macro   "t\h;vghms`;a#<space><esc>"
# helix uncomment macro "ghlmd`dd"

DIR="$(dirname "$0")"

echo
echo "---------- Compilation ---------"
start=`date +%s.%N`
g++ -include bits/stdc++.h -include lib/debug/debug.hpp -std=c++17 -DLOCAL \
-Wall -Wextra -Wconversion -Wshadow -Wfloat-equal -Wno-sign-conversion -Wno-sign-compare \
-D_GLIBCXX_NO_ASSERTIONS `# -O2` \
-fsanitize=undefined,address -g \
-o a.out $(fd -Iae cpp --changed-within 3s)
ok=$?
end=`date +%s.%N`
echo "Compilation took: $(echo "$end - $start" | bc -l)s"

if [[ $ok == 0 ]]; then
bash -c "$DIR/test.sh"
fi
