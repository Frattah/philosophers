#! /bin/bash

echo "\n\nTest #0 (uno ottocento duecento uno)"
./philo uno ottocento duecento uno

echo "\n\nTest #1 (4 9)"
./philo 4 9

echo "\n\nTest #2 (-1 800 200 200 1)"
./philo -1 800 200 200 1

echo "\n\nTest #3 (10 190 200 0)"
./philo 10 190 200 0

echo "\n\nTest #4 (1 800 200 200 1)"
./philo 1 800 200 200 1 | grep "died"

echo "\n\nTest #5 (5 800 200 200 5)"
rm -rf logs
./philo 5 800 200 200 5 > logs
grep "is eating" logs | wc -l
grep "died" logs

echo "\n\nTest #6 (5 300 200 120 1)"
rm -rf logs
./philo 5 300 200 120 1 > logs
grep "is eating" logs | wc -l
grep "died" logs

echo "\n\nTest #7 (4 410 200 200 5)"
rm -rf logs
./philo 4 410 200 200 5 > logs
grep "is eating" logs | wc -l
grep "died" logs


echo "\n\nTest #8 (4 310 200 100 10)"
rm -rf logs
./philo 4 310 200 100 10 > logs
grep "is eating" logs | wc -l
grep "died" logs


echo "\n\nTest #9 (20 800 200 200 1)"
rm -rf logs
./philo 20 800 200 200 1 > logs
grep "is eating" logs | wc -l
grep "died" logs


echo "\n\nTest #10 (50 800 200 200 1)"
rm -rf logs
./philo 50 800 200 200 1 > logs
grep "is eating" logs | wc -l
grep "died" logs

echo "\n\nTest #11 (3 410 200 200)"
rm -rf logs
./philo 3 410 200 200 > logs
grep "is eating" logs | wc -l
grep "died" logs

echo "\n"
