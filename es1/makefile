CXXFLAGS:= -Wall -pedantic

compila: buffon.x test_rnd.x inverse.x


%.x: %.o funzioni.o
	g++ $^ -o $@ -lrandom -lblas

funzioni.o: funzioni.cpp funzioni.h 
	g++ ${CXXFLAGS} $< -c

%.o: %.cpp
	g++ ${CXXFLAGS} $< -c

clean:
	rm *.o
