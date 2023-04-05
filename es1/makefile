RND:= ../random_lsn
CXXFLAGS:= -Wall -pedantic

compila: buffon.x			#main.x inverse.x


%.x: %.o random.o funzioni.o
	g++ $^ -o $@

random.o: ${RND}/random.cpp ${RND}/random.h
	g++ ${CXXFLAGS} $< -c

funzioni.o: funzioni.cpp funzioni.h 
	g++ ${CXXFLAGS} $< -c

%.o: %.cpp
	g++ ${CXXFLAGS} $< -c

clean:
	rm *.o
