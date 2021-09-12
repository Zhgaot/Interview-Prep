#!/bin/bash

g++ union_test.cpp -o union_test

g++ byteorder.cpp -o byteorder

if [ -e union_test ]; then
    mkdir -p bin && mv ./union_test ./bin
fi

if [ -e byteorder ]; then
    mkdir -p bin && mv ./byteorder ./bin
fi
