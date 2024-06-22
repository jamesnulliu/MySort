#!/bin/bash

BuildType="Release"  # Release or Debug
CleanFirst=""
# If you built Yutils as a shared library, set this to ON
SharedYutils=OFF

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        Release|Debug)
            BuildType=$1
            ;;
        -c|--clean)
            CleanFirst="--clean-first"
            ;;
        *)
            echo "Error: Invalid argument '$1'"
            exit 1
            ;;
    esac
    shift
done

PROJ_HOME=$(pwd)

if [ ! -d "$PROJ_HOME/build" ]; then
    mkdir $PROJ_HOME/build
fi

cd $PROJ_HOME/build
cmake ..  \
    -DCMAKE_BUILD_TYPE=$BuildType \
    -DSHARED_YUTILS=$ShareYutils \
    -G "Ninja"
cmake --build . --parallel $(nproc) $CleanFirst
cd $PROJ_HOME
echo "Build finished."