RND:= ../random_lsn
CXXFLG:= -Wall -pedantic




compila: RandomWalk.x main.x


%.x: funzioni.o Integranda.o %.o
	g++ $^ -o $@ -lblas -L../random_lsn -lrandom

RandomWalk.o: RandomWalk.cpp
	g++ $^ -c

main.o: main.cpp
	g++ ${CXXFLG} $^ -c

random.o: ${RND}/random.cpp ${RND}/random.h
	g++ ${CXXFLG} $< -c

%.o: %.cpp %.h
	g++ ${CXXFLG} $< -c

clean:
	rm *o
