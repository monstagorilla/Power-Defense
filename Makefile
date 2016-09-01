CXX=clang++
CXXFLAGS=-lSDL2

PowerDefense: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f *.o PowerDefense    
