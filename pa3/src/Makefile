CXX = g++
CFLAGS = -O3 -std=c++11
# CFLAGS = -g -std=c++11

EXE = router
OBJ = main.o parser.o graph.o router.o

all:$(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

clean:
	rm *.o $(EXE)