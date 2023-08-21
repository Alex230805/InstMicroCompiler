#!bin/bash


echo "Compiling .. "
gcc -c -g lib/list.c -o bin/list.o
gcc -c -g main.c -o bin/main.o
echo "Cleaning Up!"
gcc -o ISCompiler bin/*
echo "Compile finished"
