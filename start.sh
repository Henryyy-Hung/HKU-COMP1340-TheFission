#!/bin/bash

clear

export LANG=zh_CN.UTF-8

boundary="====================================================="

echo "$boundary"

echo "$0: Executable file is compiling"
cd src
make game > /dev/null

if [ -e game ]
then 
	echo "$0: Compilation sucess"
fi

mv ./game ../exe
cd ..

if [ -e ./doc/story.txt ]
then
	cp ./doc/story.txt ./exe
	echo "$0: Story document is ready"
else
	echo "$0: Story document is missed"
fi


echo "$boundary"

echo -n "$0: Start the game immeadiately? [y/n]: "
read input

if [ $input == "y" ]
then
	cd ./exe
	./game
else
	echo "$0; Process terminaed"
	echo "$boundary"
fi

