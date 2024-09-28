COPTIONS = g++ -O2 -Wall

all: project1 clean

project1: project1.o fraction.o point.o
	$(COPTIONS) -o project1 project1.o fraction.o point.o

project1.o: project1.cc fraction.h point.h
	$(COPTIONS) -c project1.cc -o project1.o

fraction.o: fraction.cc fraction.h
	$(COPTIONS) -c fraction.cc -o fraction.o

point.o: point.cc point.h fraction.h
	$(COPTIONS) -c point.cc -o point.o

clean:
	rm -f *.o
	echo "\n\nEverything compiled and cleaned!\nRun ./project1 to run program."