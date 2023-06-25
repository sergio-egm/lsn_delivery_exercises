CXXFLG:= -Wall -pedantic




compila: RandomWalk.x integral.x


%.x: funzioni.o Integranda.o %.o
	g++ $^ -o $@ -lblas -lrandom -lBlockAnalisys

RandomWalk.o: RandomWalk.cpp
	g++ $^ -c

%.o: %.cpp %.h
	g++ ${CXXFLG} $< -c

clean:
	rm *o
