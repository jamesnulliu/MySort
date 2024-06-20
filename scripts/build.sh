#!/bin/bash

build_type=$1  # Release or Debug
# If you build Yutils as a shared library, set this to ON
shared_yutils=OFF

PROJ_HOME=$(pwd)

rm -rf $PROJ_HOME/build
mkdir -p $PROJ_HOME/build
cd $PROJ_HOME/build
cmake ..  \
    -DCMAKE_BUILD_TYPE=$build_type  \
    -DSHARED_YUTILS=$shared_yutils  \
    -G "Unix Makefiles"
cmake --build . --parallel $(nproc)
cd $PROJ_HOME
echo "Build finished."