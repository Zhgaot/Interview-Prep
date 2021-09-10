#!/bin/bash

g++ main.cpp -Iinclude -std=c++11 -o test_MyString

mkdir -p bin && mv ./test_MyString ./bin
