#!/bin/bash

g++ -std=c++11 -g easy_binary_search.cpp ./src/basic_solution.cpp -o easy_binary_search
g++ -std=c++11 -g left_binary_search.cpp ./src/basic_solution.cpp -o left_binary_search
g++ -std=c++11 -g right_binary_search.cpp ./src/basic_solution.cpp -o right_binary_search

mkdir -p bin && mv ./easy_binary_search ./bin && mv ./left_binary_search ./bin && mv ./right_binary_search ./bin