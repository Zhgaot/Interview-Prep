#!/bin/bash

g++ -g anonymous-pipe.cpp -o anonymous-pipe
g++ -g fifo_r.cpp -o fifo_r
g++ -g fifo_w.cpp -o fifo_w

mkdir -p bin && mv ./anonymous-pipe ./bin && mv ./fifo_r ./bin && mv ./fifo_w ./bin