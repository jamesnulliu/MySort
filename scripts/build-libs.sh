#!/bin/bash

PROJ_HOME=$(pwd)

# Update and Init all submodules
git submodule update --init --recursive

# Build Yutils
export YUTILS_HOME="$(pwd)/vendor/Yutils"
cd $YUTILS_HOME
bash ./scripts/build.sh Release $PROJ_HOME/libs
cd $PROJ_HOME