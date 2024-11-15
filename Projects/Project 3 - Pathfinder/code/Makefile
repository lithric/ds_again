PROJECT = project3
RM_FILES = $(PROJECT).o disjointSet.o sampler.o
COPTIONS = g++ -O2 -Wall

all: $(PROJECT) clean

$(PROJECT): $(PROJECT).o disjointSet.o sampler.o
	$(COPTIONS) -o $(PROJECT) $(PROJECT).o disjointSet.o sampler.o

$(PROJECT).o: $(PROJECT).cpp output.cpp
	$(COPTIONS) -c $(PROJECT).cpp -o $(PROJECT).o

disjointSet.o: disjointSet.cpp disjointSet.h
	$(COPTIONS) -c disjointSet.cpp -o disjointSet.o

sampler.o: sampler.cpp sampler.h
	$(COPTIONS) -c sampler.cpp -o sampler.o

clean:
	rm -rf $(RM_FILES)
	echo "\n\nEverything compiled and cleaned!\nRun ./$(PROJECT) to run program."