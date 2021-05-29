#!/bin/bash

clear

boundary="====================================================="

echo "$boundary"

if [ -e ./src/game ]
then
	echo "$0: Executable file was compiled"
	chmod 700 ./exe/game
else
	echo "$0: Executable file is compiling"
	cd src
	make game > /dev/null

	if [ -e game ]
	then 
		echo "$0: Compilation sucess"
        sleep 1s
	fi

	make clean > /dev/null
	mv ./game ../exe
	cd ..
fi

if [ -e ./doc/story.txt ]
then
	cp ./doc/story.txt ./exe
	echo "$0: Story document is ready"
else
	echo "$0: Story document is missed"
fi

sleep 1s

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

