set -ev
find dep -name '*.d' | xargs grep "$1" -l | xargs --no-run-if-empty rm -v
