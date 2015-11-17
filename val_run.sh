#!/bin/bash

make clean

if g++ -std=c++11 -O1 -g *.cpp -o SocialNetwork_test; then
    valgrind --leak-check=yes ./SocialNetwork_test
fi
