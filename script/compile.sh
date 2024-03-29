#!/usr/bin/env sh

# helix comment macro   "t\h;vghms`;a#<space><esc>"
# helix uncomment macro "ghlmd`dd"

DIR="$(dirname "$0")"

echo
echo "---------- Compilation ---------"
g++ -include bits/stdc++.h -include lib/debug.h -std=c++14 -DLOCAL \
-Wall -Wextra -Wconversion -Wshadow -Wfloat-equal \
`# -O2` \
`# -fsanitize=undefined -fsanitize=address` \
-o a.out $(fd -ae cpp --changed-within 3s)

bash -c "$DIR/test.sh"
