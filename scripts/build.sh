#!/bin/bash

build_type=$1

shared_yutils=OFF

PROJECT_ROOT_DIR=$(pwd)

# rm -rf $PROJECT_ROOT_DIR/build

mkdir -p $PROJECT_ROOT_DIR/build

cd $PROJECT_ROOT_DIR/build

cmake .. -DCMAKE_BUILD_TYPE=$build_type -DSHARED_YUTILS=$shared_yutils

make -j$(nproc)

cd $PROJECT_ROOT_DIR

echo "Build finished successfully."