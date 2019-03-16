CC = g++
flag = -std=c++14
all: out

out:
	${CC} -o out ${flag} ./Sem6/IndustrialProgramming/Task1/main.cpp
test: out
	echo "nice"
