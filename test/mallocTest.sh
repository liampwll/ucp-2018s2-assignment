#/usr/bin/env bash

# Stop if a command returns non-zero
set -e

for f in ./test/inputs/*; do
    valgrind --leak-check=full --error-exitcode=1 ./TurtleGraphicsMallocTest $f
    valgrind --leak-check=full --error-exitcode=1 ./TurtleGraphicsSimpleMallocTest $f
    valgrind --leak-check=full --error-exitcode=1 ./TurtleGraphicsDebugMallocTest $f
done
