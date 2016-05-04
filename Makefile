Scheme: main.o
	g++ main.o -o Schemes
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o Scheme