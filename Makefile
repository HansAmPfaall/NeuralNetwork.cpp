CXX = g++ -std=c++11 -O3 -Wall
CHECKSTYLE = python ../cpplint.py
MAIN = $(basename $(wildcard *Main.cpp))
TEST = $(basename $(wildcard *Test.cpp))
OBJECTS = $(addsuffix .o, $(filter-out %Main %Test, $(basename $(wildcard *.cpp))))
HEADERS = $(wildcard *.h)
LIBS =

.PRECIOUS: %.o

all: clean compile run

compile: $(MAIN)

run:
	./$(MAIN)

test: $(TEST)
	for T in $(TEST); do ./$$T; done

%Main: %Main.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

%Test: %Test.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) -c $<

clean:
	@rm -f *.o
	@rm -f *.tmp
	@rm -f $(MAIN)
	@rm -f $(TEST)