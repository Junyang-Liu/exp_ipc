#!/bin/sh
g++ psenvpub.cpp -o pub -lzmq -lhiredis
g++ psenvsub.cpp -o sub -lzmq

