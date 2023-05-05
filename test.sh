#! /bin/bash

echo "\n\nTest #1 (5 800 200 200 2)"
./philo 5 800 200 200 2 | grep "is eating" | wc -l

echo "\n\nTest #2 (5 300 200 120 1)"
./philo 5 300 200 120 1 | grep "is dead" | wc -l

echo "\n\nTest #3 (4 410 200 200 2)"
./philo 4 410 200 200 2 | grep "is eating" | wc -l

echo "\n\nTest #4 (20 800 200 200 1)"
./philo 20 800 200 200 1 | grep "is eating" | wc -l

echo "\n\nTest #5 (50 800 200 200 1)"
./philo 50 800 200 200 1 | grep "is eating" | wc -l 

#echo "\n\nTest #5"
#./philo 3 410 200 200

