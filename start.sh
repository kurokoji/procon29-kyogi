#!/bin/sh

cd ./haruhi
gnome-terminal -- ruby ./haruhi.rb &

sleep 1

cd ../
gnome-terminal -- ./mikuru/build/mikuru &

cd ./nagato
gnome-terminal -- dub --compiler=ldc2 --build=release -- 1000 80 &

cd ../kyon
gnome-terminal -- ./execute.sh
