CC=gcc
CAR=ar
CRANLIB=ranlib

OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECKFLAGS=-lsubunit -lrt -lpthread -lm
else
	CHECKFLAGS=
endif


FILE1=s21_grep
FILE2=test_g


all: s21_grep

s21_grep: $(FILE1).c
	$(CC) -o ./$(FILE1) $(FLAGS) $(FILE1).c

test: $(FILE1)
	sh $(FILE2).sh

clean:
	rm -rf *.o *.a *.out
	rm -rf $(FILE1)
	cp ../../materials/linters/CPPLINT.cfg ..
	rm ../CPPLINT.cfg

style:
	cp ../../materials/linters/CPPLINT.cfg ..
	cppcheck --enable=all --suppress=missingIncludeSystem ../../src/
	python3 ../../materials/linters/cpplint.py --extensions=c ../*/*.c ../*/*.h

leaks:
	CK_FORK=no leaks --atExit -- ./s21_cat

rebuild:
	make clean
	make all
	rm -rf  *.o *.a
