all: format build_test

format:
	clang-format -i ./include/*.hpp ./src/*.cpp

build_test:
	g++ -I ./include ./src/*.cpp ./test/*.cpp -o Exe
