#!/bin/bash

gcc -g -Wall -fopenmp -o trapezoid trapezoid.c 

./trapezoid 50 5000000 -5.0 5.0
