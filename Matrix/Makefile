all: prepare build_test run_test coverage_report clean

prepare:
	bash ./scripts/format.sh
	bash ./scripts/check.sh

build_test:
	g++ -std=c++2a -Werror -I ./include -c ./src/doublearray.cpp  -o doublearray.o -lpthread -coverage -lgcov
	g++ -std=c++2a -Werror -I ./include -c ./src/doublematrix.cpp  -o doublematrix.o -lpthread -coverage -lgcov
	g++ -std=c++2a -Werror -I ./include -c ./test/main.cpp  -o main.o
	g++ -std=c++2a -Werror -I ./include *.o -o ./test/Exe -lgtest -lpthread -coverage -lgcov

run_test:
	valgrind ./test/Exe

coverage_report:
	mv *.gc* ./test
	lcov -t ./test/Exe -o ./test/coverage_report.info -c -d ./test
	genhtml -o ./test/coverage_report ./test/coverage_report.info

clean:
	rm *.o
