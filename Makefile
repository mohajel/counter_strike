# in the name of God

CC = g++ -std=c++11
EXE_FILE = a.out

$(EXE_FILE): Error.o Shop.o Manager.o Player.o main.o
	$(CC) Error.o Shop.o Manager.o Player.o main.o -o $(EXE_FILE)

main.o:	main.cpp Manager.hpp
	$(CC) -c main.cpp -o main.o

Manager.o: Manager.cpp Manager.hpp
	$(CC) -c Manager.cpp -o Manager.o

Error.o: Error.cpp Error.hpp
	$(CC) -c Error.cpp -o Error.o

Player.o: Player.cpp Player.hpp
	$(CC) -c Player.cpp -o Player.o

Shop.o: Shop.cpp Shop.hpp
	$(CC) -c Shop.cpp -o Shop.o

clean:
	rm *o $(EXE_FILE)