set -ev
make buildtype=debug   dotout=no  verbose=no  -j8
make buildtype=debug   dotout=no  verbose=yes -j8
make buildtype=debug   dotout=yes verbose=no  -j8
make buildtype=debug   dotout=yes verbose=yes -j8
make buildtype=test    dotout=no  verbose=no  -j8
make buildtype=test    dotout=no  verbose=yes -j8
make buildtype=test    dotout=yes verbose=no  -j8
make buildtype=test    dotout=yes verbose=yes -j8
make buildtype=release dotout=no  verbose=no  -j8
make buildtype=release dotout=no  verbose=yes -j8
make buildtype=release dotout=yes verbose=no  -j8
make buildtype=release dotout=yes verbose=yes -j8
