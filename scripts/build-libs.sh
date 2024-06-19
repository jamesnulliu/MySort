#!/bin/bash
ProjHome=$(pwd)
BuildType=Release
UpdateLibs=false
SharedYutils=false

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        Release|Debug)
            BuildType=$1
            ;;
        -u|--update)
            UpdateLibs=true
            ;;
        --shared-yutils)
            SharedYutils=true
            ;;
        *)
            echo "Error: Invalid argument '$1'"
            exit 1
            ;;
    esac
    shift
done

export YUTILS_HOME="$ProjHome/vendor/Yutils"

if [ ! -d "$YUTILS_HOME" ] || [ "$(find "$YUTILS_HOME" -mindepth 1 | wc -l)" -eq 0 ]; then
    git submodule update --init --recursive
elif [ "$UpdateLibs" = "true" ]; then
    git submodule update --remote --recursive
fi

cd $YUTILS_HOME
if [ "$SharedYutils" = "true" ]; then
    bash ./scripts/build.sh Release --clean-all --shared 
else
    bash ./scripts/build.sh Release --clean-all
fi
cd $ProjHome
