#!/bin/bash

BUILD_TYPE="Ninja"
BUILD_SUFFIX="ninja"

BUILD_FOLDER="build_$BUILD_SUFFIX"
SOURCE_FOLDER="."

if [ ! -d "$BUILD_FOLDER" ]; then
    mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER"

cmake -G "$BUILD_TYPE" "../$SOURCE_FOLDER"
cmake --build .

cd ..