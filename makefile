	
output: main.o linkedlist.o polycalculator.o
	g++ main.o linkedlist.o polycalculator.o
	
main.o: main.cpp
	g++ -c main.cpp

Linkedlist.o: Linkedlist.cpp Linkedlist.h
		g++ -c Linkedlist.cpp
polycalculator.o: polycalculator.cpp polycalculator.h
		g++ -c polycalculator.cpp

clean:
	rm *.o output
