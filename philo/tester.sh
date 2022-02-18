#!/bin/bash

# Philosophers

NAME=philosophers
PATH=./

# Variables
DLY=5s

ulimit -t 42

# Colors
WHT='\033[0m'
RED='\033[0;31m'
GRN='\033[0;32m'
YEL='\033[0;33m'
CYN='\033[0;36m'

# functions

function iloop() {
	printf "$CYN\n@: $PATH$NAME $1 $2 $3 $4 $WHT\n"
	RET=$($PATH$NAME $1 $2 $3 $4 | /usr/bin/grep died)
	if [ ! -z "$RET" ]; then
		printf "$RED $RET KO $WHT";
	else
		printf "$GRN OK $WHT";
	fi
}

function iloop_eat() {
	printf "$CYN\n@: $PATH$NAME $1 $2 $3 $4 $5 $WHT\n"
	RET=$($PATH$NAME $1 $2 $3 $4 $5 | /usr/bin/grep died)
	if [ ! -z "$RET" ]; then
		printf "$RED $RET KO $WHT";
	else
		printf "$GRN OK $WHT";
	fi
}

function iloop_die() {
	printf "$CYN\n@: $PATH$NAME $1 $2 $3 $4 $WHT\n"
	RET=$($PATH$NAME $1 $2 $3 $4 | /usr/bin/grep died)
	if [ ! -z "$RET" ]; then
		printf "$GRN OK $WHT";
	else
		printf "$RED $RET KO $WHT";
	fi
}

# TEST 1

if [ ! -f "$PATH$NAME" ]; then
	printf "Cannot find executable file. Searching at $PATH$NAME"
	exit 1
fi

if [ -z "$1" ] || ([ ! -z "$1" ] && [ "$1" == "1" ]); then
	printf "\n$GRN TEST 1 [Invalid paremeters]\n$WHT"
	printf "$YEL Your program should stop\n$WHT"

	printf "$CYN\n@: $PATH$NAME$WHT\n"
		$PATH$NAME
	printf "$CYN\n@: $PATH$NAME 1\n$WHT"
		$PATH$NAME 1
	printf "$CYN\n@: $PATH$NAME 1 2\n$WHT"
		$PATH$NAME 1 2
	printf "$CYN\n@: $PATH$NAME 1 2 3\n$WHT"
		$PATH$NAME 1 2 3
	printf "$CYN\n@: $PATH$NAME 1 2 3 4 5 6\n$WHT"
		$PATH$NAME 1 2 3 4 5 6
	printf "$CYN\n@: $PATH$NAME 0 100 100 100\n$WHT"
		$PATH$NAME 0 100 100 100
	printf "$CYN\n@: $PATH$NAME 1 -1 100 100\n$WHT"
		$PATH$NAME 1 -1 100 100
	printf "$CYN\n@: $PATH$NAME 1 100 -1 100\n$WHT"
		$PATH$NAME 1 100 -1 100
	printf "$CYN\n@: $PATH$NAME 1 100 100 -1\n$WHT"
		$PATH$NAME 1 100 100 -1
	printf "$CYN\n@: $PATH$NAME 1 100 100 100 0\n$WHT"
		$PATH$NAME 1 100 100 100 0

	printf "$GRN \nSpecial case [One philosopher]\n$WHT"
	printf "$YEL Shouldn't be able to eat\n$WHT"
	printf "$CYN\n@: $PATH$NAME 1 800 100 100\n$WHT"
		$PATH$NAME 1 800 100 100
fi

# TEST 2
if [ -z "$1" ] || ([ ! -z "$1" ] && [ "$1" == "2" ]); then
	printf "\n$GRN TEST 2 [Infinite loops]\n$WHT"
	printf "$YEL No philosopher should die\n$WHT"

	iloop 2 410 200 200
	iloop 2 130 60 60
	iloop 3 1000 300 300
	iloop 4 350 150 150
	iloop 5 800 200 200
	printf "\n";
fi

# TEST 3
if [ -z "$1" ] || ([ ! -z "$1" ] && [ "$1" == "3" ]); then
	printf "\n$GRN TEST 3 [Eat count] (Doesn't check for infinite loop) $WHT\n"
	printf "$YEL No philosopher should die\n$WHT"
	printf "$YEL Program must end after all have eaten\n$WHT"

	iloop_eat 2 410 200 200 10
	iloop_eat 2 130 60 60 10
	iloop_eat 3 1000 300 300 10
	iloop_eat 4 600 150 150 10
	iloop_eat 4 350 150 150 10
	iloop_eat 5 800 200 200 10
	printf "\n";
fi

# TEST 4
if [ -z "$1" ] || ([ ! -z "$1" ] && [ "$1" == "4" ]); then
	printf "\n$GRN TEST 4 [Dies] (Doesn't check for infinite loop) $WHT\n"
	printf "$YEL Philosopher should die\n$WHT"

	iloop_die 2 400 200 200
	iloop_die 2 120 60 60
	iloop_die 3 500 300 300
	iloop_die 4 300 150 150
	iloop_die 4 310 200 100
	iloop_die 5 600 200 200
	printf "\n";
fi
