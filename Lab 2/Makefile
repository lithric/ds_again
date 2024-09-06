COPTIONS = g++ -O2 -Wall

all: ftest clean

ftest: ftest.o fraction.o
	$(COPTIONS) -o ftest ftest.o fraction.o

ftest.o: ftest.cc fraction.h
	$(COPTIONS) -c ftest.cc

fraction.o: fraction.cc fraction.h
	$(COPTIONS) -c fraction.cc

clean:
	rm -f *.o
	echo "everything done"