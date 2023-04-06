CXXFLAGS:= -Wall -pedantic

compila: buffon.x main.x inverse.x


%.x: %.o funzioni.o
	g++ $^ -o $@ -lrandom

funzioni.o: funzioni.cpp funzioni.h 
	g++ ${CXXFLAGS} $< -c

%.o: %.cpp
	g++ ${CXXFLAGS} $< -c

clean:
	rm *.o
