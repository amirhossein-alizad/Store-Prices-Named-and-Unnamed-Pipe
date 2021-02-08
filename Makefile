CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c
all: StoreCalculator.out States.out Cities.out Shops.out

StoreCalculator.out: Main.o tools.o
	$(CC) Main.o tools.o $(FLAGS) -o StoreCalculator.out

States.out: states.o tools.o
	$(CC) states.o tools.o $(FLAGS) -o States.out

Cities.out: cities.o tools.o
	$(CC) cities.o tools.o $(FLAGS) -o Cities.out

Shops.out: shops.o tools.o
	$(CC) shops.o tools.o $(FLAGS) -o Shops.out

shops.o: shops.cpp tools.h
	$(CC) $(COMPILE_FLAGS) shops.cpp

cities.o: cities.cpp tools.h
	$(CC) $(COMPILE_FLAGS) cities.cpp

states.o: states.cpp tools.h
	$(CC) $(COMPILE_FLAGS) states.cpp

Main.o: Main.cpp tools.h
	$(CC) $(COMPILE_FLAGS) Main.cpp

tools.o: tools.cpp tools.h
	$(CC) $(COMPILE_FLAGS) tools.cpp

.PHONY: clean

clean:
				rm *.o
				rm *.out
