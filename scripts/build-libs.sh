#!/bin/bash

PROJ_HOME=$(pwd)

# Update and Init all submodules
git submodule update --init --recursive

# Build Yutils
export YUTILS_HOME="$PROJ_HOME/vendor/Yutils"
cd $YUTILS_HOME
bash ./scripts/build.sh Release --libo $PROJ_HOME/lib
cd $PROJ_HOME
