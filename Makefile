Scheme: utils.o cell.o main.o scheme_procedure.o
	g++ utils.o cell.o main.o scheme_procedure.o -o Scheme

utils.o: utils.cpp
	g++ -c utils.cpp

cell.o: cell.cpp
	g++ -c cell.cpp

scheme_procedure.o: scheme_procedure.cpp
	g++ -c scheme_procedure.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o Scheme