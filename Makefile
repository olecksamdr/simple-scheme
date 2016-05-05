Scheme: cell.o main.o
	g++ cell.o main.o -o Scheme

cell.o: cell.cpp
	g++ -c cell.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o Scheme