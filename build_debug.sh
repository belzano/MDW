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

if [ ! -d "debug" ]; then
	mkdir debug
fi
cd debug

cmake -DCMAKE_BUILD_TYPE=Debug ../../../MDW && make
