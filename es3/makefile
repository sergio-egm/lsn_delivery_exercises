CXXFLAGS:=-Wall -pedantic


compila: main.x


main.x: main.o Black-Scholes.o funzioni.o random.o
	g++ $^ -o $@

random.o: ../random_lsn/random.o
	cp $^ .

main.o: main.cpp
	g++ ${CXXFLAGS} $< -c -L -lrandom

%.o: %.cpp %.h
	g++ ${CXXFLAGS} $< -c -L -lrandom