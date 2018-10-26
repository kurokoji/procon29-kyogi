#!/bin/sh

cd ./mikuru
mkdir build
cd build
cmake ..
make

cd ../../
cd ./kyon
./build.sh

cd ../
cd ./nagato
dub build --build=release --compiler=ldc2
