set -ev
make platform=linux buildtype=debug   dotout=no verbose=yes -j
make platform=linux buildtype=test    dotout=no verbose=yes -j
make platform=linux buildtype=release dotout=no verbose=yes -j
zest ./tests
