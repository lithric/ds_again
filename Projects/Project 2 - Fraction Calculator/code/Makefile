PROJECT = project2
RM_FILES = $(PROJECT).o fraction.o
COPTIONS = g++ -O2 -Wall

all: $(PROJECT) clean

$(PROJECT): $(PROJECT).o stack.h stack.cc fraction.h fraction.cc
	$(COPTIONS) -c $(PROJECT).cc -o $(PROJECT)

$(PROJECT).o: $(PROJECT).cc stack.h fraction.h
	$(COPTIONS) -c $(PROJECT).cc -o $(PROJECT).o

clean:
	rm -rf $(RM_FILES)
	echo "\n\nEverything compiled and cleaned!\nRun ./$(PROJECT) to run program."