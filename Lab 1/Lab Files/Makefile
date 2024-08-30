COPTIONS = g++ -O2 -Wall

all: lab1 clean

lab1: main.o read.o sort.o print.o
	$(COPTIONS) -o lab1 main.o read.o sort.o print.o

main.o: main.cc lab1.h
	$(COPTIONS) -c main.cc

read.o: read.cc lab1.h
	$(COPTIONS) -c read.cc

sort.o: sort.cc lab1.h
	$(COPTIONS) -c sort.cc

print.o: print.cc lab1.h
	$(COPTIONS) -c print.cc

clean:
	rm -f *.o
	echo Clean has been cleanly