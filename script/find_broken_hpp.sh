#!/usr/bin/env bash

# Usage:
#   ./check_headers.sh -std=c++20 -Iinclude -DMYFLAG=1
#
# Collects compiler flags from argv and checks all .hpp files.

# Save compiler flags from argv
flags=("$@")

# Find all .hpp files
mapfile -t files < <(fd -e hpp -a)
total=${#files[@]}

if [ "$total" -eq 0 ]; then
  echo "No .hpp files found."
  exit 0
fi

width=${#total}
bar_width=50
i=0
last_percent=-1
warned=()

draw_bar() {
  local force=${1:-0}
  local percent=$((i * 100 / total))

  if [ "$percent" -ne "$last_percent" ] || [ "$force" -eq 1 ]; then
    local filled=$((percent * bar_width / 100))
    local empty=$((bar_width - filled))

    local bar=$(printf "%0.s#" $(seq 1 $filled))
    local space=$(printf "%0.s " $(seq 1 $empty))

    printf "\r[%s%s] %3d%% (%*d/%d)" \
      "$bar" "$space" "$percent" "$width" "$i" "$total"

    last_percent=$percent
  fi
}

for file in "${files[@]}"; do
  ((i++))
  draw_bar

  # Compile header as a dummy translation unit to check for warnings
  if output=$(g++ -fsyntax-only -Wall -Wextra "${flags[@]}" -xc++ - <<EOF 2>&1
#include <bits/stdc++.h>
using namespace std;
#include "$file"
EOF
  ); then
    if [ -n "$output" ]; then
      printf "\r\033[K"
      echo "⚠️  $file"
      warned+=("$file")
    else
      printf "\r\033[K"
      echo "✅ $file"
    fi
  else
    printf "\r\033[K"
    echo "❌ $file"
    warned+=("$file")
  fi

  draw_bar 1
done

echo -e "\nDone."

# Summary of problematic headers
if [ "${#warned[@]}" -gt 0 ]; then
  echo -e "\nHeaders with warnings/errors:"
  printf '  %s\n' "${warned[@]}"
else
  echo -e "\nAll headers are warning-free 🎉"
fi
