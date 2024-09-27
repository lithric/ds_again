PROJECT = project2
RM_FILES = $(PROJECT).o fraction.o unsortedDictionary.o dictionary.o
COPTIONS = g++ -O2 -Wall

all: $(PROJECT) clean

$(PROJECT): $(PROJECT).o fraction.o
	$(COPTIONS) -o $(PROJECT) $(PROJECT).o fraction.o

$(PROJECT).o: $(PROJECT).cc fraction.h stack.cc stack.h
	$(COPTIONS) -c $(PROJECT).cc -o $(PROJECT).o

fraction.o: fraction.cc fraction.h
	$(COPTIONS) -c fraction.cc -o fraction.o

clean:
	rm -rf $(RM_FILES)
	echo "\n\nEverything compiled and cleaned!\nRun ./$(PROJECT) to run program."