
BUILD_TYPE="Ninja"
SOURCE_FOLDER="Hw"

cmake -G ${BUILD_TYPE} ../${SOURCE_FOLDER}
cmake --build .
