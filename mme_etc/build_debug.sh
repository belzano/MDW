#!/bin/sh

cd ..

if [ ! -d "build" ]; then
	mkdir build
fi
cd build

if [ ! -d "debug" ]; then
	mkdir debug
fi
cd debug

cmake -DCMAKE_BUILD_TYPE=Debug ../../MME/src && make
