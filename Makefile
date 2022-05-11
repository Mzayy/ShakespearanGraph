EXENAME = main
OBJS = main.o wordgraph.o

CXX = clang++
CXXFLAGS =  -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

.PHONY: all test clean

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp wordgraph.h
	$(CXX) $(CXXFLAGS) main.cpp

wordgraph.o : wordgraph.cpp wordgraph.h
	$(CXX) $(CXXFLAGS) wordgraph.cpp

test: tests.o catchmain.o $(OBJS)
	$(LD) catchmain.o tests.o wordgraph.o $(LDFLAGS) -o test

catchmain.o: catch/catchmain.cpp catch/catch.hpp 
	$(CXX) $(CXXFLAGS)  catch/catchmain.cpp

tests.o: tests.cpp catch/catch.hpp wordgraph.h wordgraph.cpp 
	$(CXX) catchmain.o $(CXXFLAGS) tests.cpp

clean:
	@rm -f $(OBJS) core