#!/bin/bash

g++ -g msg_receive.cpp -o msg_receive
g++ -g msg_send.cpp -o msg_send

mkdir -p bin && mv ./msg_receive ./bin && mv ./msg_send ./bin