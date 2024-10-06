## Auto compile and testing script.
## Note: You have to close this script with Ctrl-C, else watchexec would still
## be running.

#!/usr/bin/env sh

killall -q watchexec
while pgrep -u $UID -x watchexec >/dev/null; do sleep 1; done

export DIR="$(dirname "$0")"

# https://stackoverflow.com/a/52033580
# (trap 'kill 0' SIGINT; watchexec -pe cpp $DIR/compile.sh & watchexec -pe inp $DIR/test.sh)

# https://stackoverflow.com/a/44124618
xargs -P 0 -I {} sh -c 'eval "$1"' - {} <<'EOF'
watchexec --no-vcs-ignore -i="stress_test*/*" -pe cpp $DIR/compile.sh
watchexec --no-vcs-ignore -pe inp $DIR/test.sh
EOF
