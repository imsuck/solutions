#!/usr/bin/env bash

# Get all .cpp files as absolute paths
mapfile -t files < <(fd -e cpp -a)
total=${#files[@]}

if [ "$total" -eq 0 ]; then
    echo "No .cpp files found."
    exit 0
fi

cnt_pad=${#total}
bar_width=50  # number of chars for the progress bar
i=0
failed_files=()

draw_bar() {
    local percent filled empty bar space
    percent=$((i * 100 / total))

    filled=$((percent * bar_width / 100))
    empty=$((bar_width - filled))

    bar=$(printf "%0.s#" $(seq 1 $filled))
    space=$(printf "%0.s " $(seq 1 $empty))

    printf "\r[%s%s] %3d%% (%*d/%d)" \
        "$bar" "$space" "$percent" "$cnt_pad" "$i" "$total"
}

for file in "${files[@]}"; do
    ((i++))

    # draw the progress bar
    draw_bar

    if g++ -I library -std=c++17 -fsyntax-only $@ "$file" >/dev/null 2>&1; then
        # clear line, print result
        printf "\r\033[K"
        echo "✅ $file"
    else
        printf "\r\033[K"
        echo "❌ $file"
        failed_files+=("$file")
    fi

    # redraw progress bar after printing result
    draw_bar
done

if [ "${#failed[@]}" -gt 0 ]; then
    echo -e "\nFailed files:"
    printf '  %s\n' "${failed[@]}"
else
    echo -e "\nAll files compiled successfully 🎉"
fi
