
BUILD_TYPE="Ninja"
SOURCE_FOLDER="Hw"

cmake -G ${BUILD_TYPE} ../${SOURCE_FOLDER}
cmake --build .

mkdir build
exclude_dirs="lib CMakeFiles unit_test_HoareSort build"

for dir in */; do
    dir=${dir%/}
    exclude=0
    for exclude_dir in $exclude_dirs; do
        if [ "$dir" = "$exclude_dir" ]; then
            exclude=1
            break
        fi
    done

    if [ $exclude -eq 0 ]; then
        mkdir "build/$dir"
        mv "./$dir/$dir" "./build/$dir/$dir"
    fi
done

ctest -j N --output-on-failure
