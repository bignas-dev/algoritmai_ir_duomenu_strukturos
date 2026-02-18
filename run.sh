#!/bin/bash

if [ "$1" == "a" ]; then
    exit 69
fi

if [ "$1" == "a" ]; then
    exit 69
fi

if [ "$1" == "c" ]; then
    gcc c_uzd.c -Wall -Wextra -o exec && ./exec
    exit 0;
fi

if [ "$1" == "d" ]; then
    exit 69
fi

echo "Invalid argument: '$1' (blank == not supplied)"
exit 67

