all: prepare build_test run_test coverage_report

prepare:
	clang-format -i ./include/*.hpp ./src/*.cpp ./test/*.cpp
	clang-tidy ./include/*.hpp ./src/*.cpp ./test/*.cpp -extra-arg=-std=c++2a -- -I./include

build_test:
	g++ -std=c++2a -Werror -I ./include ./src/*.cpp ./test/*.cpp -o ./test/Exe -lgtest -lpthread -coverage -lgcov

run_test:
	valgrind ./test/Exe

coverage_report:
	lcov -t ./test/Exe -o ./test/coverage_report.info -c -d ./test
	genhtml -o ./test/coverage_report ./test/coverage_report.info
