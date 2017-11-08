all:
	g++ -std=c++14 ./src/main.cpp ./src/population.cpp ./src/chromosome.cpp -o ga


test:
	g++ -std=c++14 ./src/chromosome.cpp ./src/population.cpp ./src/tests/ga_test.cpp -o test
	./test
	rm test
