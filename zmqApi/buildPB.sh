#!/bin/sh
g++ psenvpub.cpp -o pub -lzmq
g++ psenvsub.cpp -o sub -lzmq

