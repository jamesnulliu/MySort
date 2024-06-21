#!/bin/bash

PROJ_HOME=$(pwd)

export YUTILS_HOME="$PROJ_HOME/vendor/Yutils"

if [ -d "$PROJ_HOME/vendor/Yutils" ]; then
    git submodule update --remote
else
    git submodule update --init --recursive
fi

# Build Yutils
cd $YUTILS_HOME
bash ./scripts/build.sh Release --libo $PROJ_HOME/lib
cd $PROJ_HOME
