CXX = g++ 
CFLAGS = -O3 -std=c++11
# CFLAGS = -g -std=c++11

EXE = mps
OBJ = main.o maxPlanarSubset.o

add:$(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CFLAGS) -o ../$@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm *.o ../$(EXE)
