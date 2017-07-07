#!/bin/sh

cd ..

if [ ! -d "deploy" ]; then
	mkdir deploy
	echo "Created directory deploy/"
fi
cd deploy

if [ ! -d "log" ]; then
	mkdir log
	echo "Created directory deploy/log/"
fi

if [ ! -d "data" ]; then
	mkdir data
	echo "Created directory deploy/data/"
fi

if [ ! -d "etc" ]; then
	ln -sfn ../MME/etc etc
	echo "symlink-ed deploy/etc/ to MME/etc/"
fi

if [ ! -d "lib" ]; then
	ln -sfn ../build/lib lib
	echo "symlink-ed deploy/lib/ to build/lib/"
fi

if [ ! -d "bin" ]; then
	ln -sfn ../build/bin bin
	echo "symlink-ed deploy/bin/ to build/bin/"
fi

if [ ! -d "../build/lib" ] || [ ! -d "../build/bin" ]; then
	echo "[WARN] build/lib or build/bin are not defined: let's try to fix that"
	cd ../build
	if [ -d "debug" ]; then
		ln -sfn debug/lib lib
		echo "symlink-ed build/lib/ to build/debug/lib/"
		ln -sfn debug/bin bin
		echo "symlink-ed build/bin/ to build/debug/bin/"
	elif [ -d "release" ]; then
		ln -sfn release/lib lib
		echo "symlink-ed build/lib/ to build/release/lib/"
		ln -sfn release/bin bin
		echo "symlink-ed build/bin/ to build/release/bin/"	
	else
		echo "No lib found: build, then try to deploy again"
	fi
fi

