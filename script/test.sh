#!/usr/bin/env sh

TIME_FMT="Time: %es Mem: %MKB"
RUN_CMD="./a.out < a.inp; echo"

echo
echo "------------- Test -------------"
if command -v systemd-run &>/dev/null; then
  /usr/bin/time -f "$TIME_FMT" \
    systemd-run --scope -p MemoryMax=512M -q --user bash -c "$RUN_CMD"
else
  /usr/bin/time -f "$TIME_FMT" bash -c "$RUN_CMD"
fi
