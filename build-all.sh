set -ev
unset on_error
make platform=linux   buildtype=debug   dotout=no  verbose=no  -j
make platform=linux   buildtype=debug   dotout=no  verbose=yes -j
make platform=linux   buildtype=debug   dotout=yes verbose=no  -j
make platform=linux   buildtype=debug   dotout=yes verbose=yes -j
make platform=linux   buildtype=test    dotout=no  verbose=no  -j
make platform=linux   buildtype=test    dotout=no  verbose=yes -j
make platform=linux   buildtype=test    dotout=yes verbose=no  -j
make platform=linux   buildtype=test    dotout=yes verbose=yes -j
make platform=linux   buildtype=release dotout=no  verbose=no  -j
make platform=linux   buildtype=release dotout=no  verbose=yes -j
make platform=linux   buildtype=release dotout=yes verbose=no  -j
make platform=linux   buildtype=release dotout=yes verbose=yes -j
make platform=windows buildtype=debug   dotout=no  verbose=no  -j
make platform=windows buildtype=debug   dotout=no  verbose=yes -j
make platform=windows buildtype=debug   dotout=yes verbose=no  -j
make platform=windows buildtype=debug   dotout=yes verbose=yes -j
make platform=windows buildtype=test    dotout=no  verbose=no  -j
make platform=windows buildtype=test    dotout=no  verbose=yes -j
make platform=windows buildtype=test    dotout=yes verbose=no  -j
make platform=windows buildtype=test    dotout=yes verbose=yes -j
make platform=windows buildtype=release dotout=no  verbose=no  -j
make platform=windows buildtype=release dotout=no  verbose=yes -j
make platform=windows buildtype=release dotout=yes verbose=no  -j
make platform=windows buildtype=release dotout=yes verbose=yes -j
