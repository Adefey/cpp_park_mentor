all: prepare build_test

prepare:
	clang-format -i ./include/*.hpp ./src/*.cpp ./test/*.cpp
	clang-tidy ./include/*.hpp ./src/*.cpp ./test/*.cpp -extra-arg=-std=c++2a -- -I./include

build_test:
	g++ -std=c++2a -Werror -I ./include ./src/*.cpp ./test/*.cpp -o Exe -lgtest
