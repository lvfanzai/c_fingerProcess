#!/bin/bash
mkdir -p build
pushd build
cmake ..
make -j 8

cp ./binarize ..
cp ./direction ..
cp ./enhancer ..
cp ./mask ..
cp ./minutia ..
cp ./thinner ..
popd


