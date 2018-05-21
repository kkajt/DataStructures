CC = g++
FLAGS = -std=c++11

all: main

main: main.o BST.o RBT.o hmap.o list.o
	$(CC) $(FLAGS) -o main main.o BST.o RBT.o hmap.o list.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

BST.o: BST.cpp
	$(CC) $(FLAGS) -c BST.cpp

RBT.o: RBT.cpp
	$(CC) $(FLAGS) -c RBT.cpp

hmap.o: hmap.cpp
	$(CC) $(FLAGS) -c hmap.cpp

list.o: list.cpp
	$(CC) $(FLAGS) -c list.cpp

clean:
	rm -f *.o *~
	rm -f main
	