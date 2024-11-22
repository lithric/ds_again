PROJECT = project4
RM_FILES = $(PROJECT).o
COPTIONS = g++ -O2 -Wall

all: $(PROJECT) clean

$(PROJECT): $(PROJECT).o
	$(COPTIONS) -o $(PROJECT) $(PROJECT).o

$(PROJECT).o: $(PROJECT).cpp
	$(COPTIONS) -c $(PROJECT).cpp -o $(PROJECT).o

clean:
	rm -rf $(RM_FILES)
	echo "\n\nEverything compiled and cleaned!\nRun ./$(PROJECT) to run program."