#!/bin/bash

mkdir -p build && cd build

pwd
ls ../
ls ../../
ls ../../imgui/
ls ../../imgui/nfd/
ls ../../imgui/nfd/src
echo "'cmake ..'"

if [ -n "$COVERAGE" ]
then
    cmake -DWITH_COVERAGE=On -DCMAKE_BUILD_TYPE=Debug ..
else
    cmake -DCMAKE_BUILD_TYPE=Debug ..
fi

echo "'build'"

cmake --build .

export CTEST_OUTPUT_ON_FAILURE=1
make test

if [ -n "$COVERAGE" ]
then
    echo "Coverage...."
    bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"
fi
