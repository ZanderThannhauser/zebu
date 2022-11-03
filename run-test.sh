set -ev
make platform=linux buildtype=release dotout=no verbose=yes -j
zest ./tests
