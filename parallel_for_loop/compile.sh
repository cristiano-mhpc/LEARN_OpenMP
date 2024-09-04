#!/bin/bash

gcc -g -Wall -fopenmp -o trapezoid trapezoid.c 

./trapezoid 80 80000000 -5.0 5.0
