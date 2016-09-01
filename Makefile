CXX=clang++
CXXFLAGS=-O2
LIBS=-lSDL2

PowerDefense: main.cpp Enemy.o Sprite.o Tower.o
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $<

Enemy.o: Enemy.cpp Enemy.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Tower.o: Tower.cpp Tower.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<  

Sprite.o: Sprite.cpp Sprite.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Point.o: Point.cpp Point.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f *.o PowerDefense
