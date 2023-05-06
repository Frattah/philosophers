#! /bin/bash

echo "\n\nTest #0 (1 800 200 200 1)"
./philo 1 800 200 200 1 | grep "died"

echo "\n\nTest #1 (5 800 200 200 10)"
./philo 5 800 200 200 10 | grep "is eating" | wc -l

echo "\n\nTest #2 (5 300 200 120 5)"
./philo 5 300 200 120 1 | grep "died"

echo "\n\nTest #3 (4 410 200 200 10)"
./philo 4 410 200 200 10 | grep "is eating" | wc -l

echo "\n\nTest #4 (4 310 200 100 10)"
./philo 4 310 200 100 10 | grep "died"

echo "\n\nTest #5 (20 800 200 200 1)"
./philo 20 800 200 200 1 | grep "is eating" | wc -l

echo "\n\nTest #6 (50 800 200 200 1)"
./philo 50 800 200 200 1 | grep "is eating" | wc -l 

echo "\n\nTest #7 (3 410 200 200)"
./philo 3 410 200 200 | grep "died"

echo "\n"
