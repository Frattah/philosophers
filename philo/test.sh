#! /bin/bash

# HINT
# Condizioni di sopravvivenza: tte + tts <= ttd
#			  	      e
#			 pari: tte <= ttd/2
#		      dispari: tte <= ttd/3

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

echo "\n\nTest #5 (2 400 100 300 10)"
rm -rf logs
./philo 2 400 100 300 10 > logs
grep "is eating" logs | wc -l
grep "died" logs

echo "\n\nTest #6 (5 800 200 200 5)"
rm -rf logs
./philo 5 800 200 200 5 > logs
grep "is eating" logs | wc -l
grep "died" logs

echo "\n\nTest #7 (5 300 200 120 1)"
rm -rf logs
./philo 5 300 200 120 1 > logs
grep "is eating" logs | wc -l
grep "died" logs

echo "\n\nTest #8 (4 410 200 200 5)"
rm -rf logs
./philo 4 410 200 200 5 > logs
grep "is eating" logs | wc -l
grep "died" logs


echo "\n\nTest #9 (4 310 200 100 10)"
rm -rf logs
./philo 4 310 200 100 10 > logs
grep "is eating" logs | wc -l
grep "died" logs


echo "\n\nTest #10 (20 800 200 200 1)"
rm -rf logs
./philo 20 800 200 200 1 > logs
grep "is eating" logs | wc -l
grep "died" logs


echo "\n\nTest #11 (50 800 200 200 1)"
rm -rf logs
./philo 50 800 200 200 1 > logs
grep "is eating" logs | wc -l
grep "died" logs


echo "\n\nTest #12 (100 800 200 200 10)"
rm -rf logs
./philo 100 800 200 200 10 > logs
grep "is eating" logs | wc -l
grep "died" logs


echo "\n\nTest #13 (200 900 200 200 10)"
rm -rf logs
./philo 200 900 200 200 10 > logs
grep "is eating" logs | wc -l
grep "died" logs

echo "\n\nTest #14 (3 410 200 200)"
rm -rf logs
./philo 3 410 200 200 > logs
grep "is eating" logs | wc -l
grep "died" logs

rm -rf logs
echo "\n"

#echo "\n\nFinal Test #15 (200 800 200 200)"
#./philo 200 800 200 200

