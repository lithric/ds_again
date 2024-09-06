COPTIONS = g++ -O2 -Wall

all: project1 clean

project1: project1.o fraction.o point.o
	$(COPTIONS) -o project1 project1.o fraction.o point.o

project1.o: project1.cc fraction.h point.h
	$(COPTIONS) -c project1.cc

fraction.o: fraction.cc fraction.h
	$(COPTIONS) -c fraction.cc

point.o: point.cc point.h fraction.h
	$(COPTIONS) -c point.cc

clean:
	rm -f *.o
	echo "everything done"