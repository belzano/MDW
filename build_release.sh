#!/bin/sh

cd ..

if [ ! -d "build" ]; then
	mkdir build
fi
cd build

if [ ! -d "MDW" ]; then
	mkdir MDW
fi
cd MDW

if [ ! -d "release" ]; then
	mkdir release
fi
cd release

cmake -DCMAKE_BUILD_TYPE=Release ../../../MDW && make
