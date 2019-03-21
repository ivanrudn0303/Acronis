CC = g++
base_path = ./Sem6/IndustrialProgramming/
flag = -std=c++11

all: task1 task2

task1:
	-${CC} -o ${base_path}Task1/out.o ${flag} ${base_path}Task1/main.cpp

task2:
	-${CC} -o ${base_path}Task2/out.o ${flag} ${base_path}Task2/main.cpp ${base_path}Task2/Liba.h ${base_path}Task2/Liba.cpp

test_task1: task1

test: test_task1
	-cat ${base_path}Task1/input.data | ${base_path}Task1/out.o > ${base_path}Task1/output.data
	-diff ${base_path}Task1/output.data ${base_path}Task1/answer.data
clean_task1:
	-rm -rf ${base_path}Task1/out*

clean_task2:
	-rm -rf ${base_path}Task2/out*
