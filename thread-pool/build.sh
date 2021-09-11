#!/bin/bash

g++ thread_test.cpp -Iinclude -lpthread -std=c++11 -o thread_test

mkdir -p bin && mv ./thread_test ./bin