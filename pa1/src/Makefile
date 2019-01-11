CXX = g++
CFLAGS = -O3 -std=c++11
CFLAGS = -g -std=c++11

EXE = insertionSort mergeSort heapSort quickSort
OBJ = parser.o stringClass.o 

all:$(EXE)

insertionSort: $(OBJ) insertionSort.o
	$(CXX) $(CFLAGS) -o ../$@ $^

mergeSort: $(OBJ) mergeSort.o
	$(CXX) $(CFLAGS) -o ../$@ $^

heapSort: $(OBJ) heapSort.o
	$(CXX) $(CFLAGS) -o ../$@ $^

quickSort: $(OBJ) quickSort.o
	$(CXX) $(CFLAGS) -o ../$@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm *.o ../*Sort                 