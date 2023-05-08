CXXFLAGS:= -Wall -pedantic

compila: buffon.x test_rnd.x dice.x


%.x: %.o funzioni.o BlockAnalisys.o
	g++ $^ -o $@ -lrandom -lblas

%.o: %.cpp %.h
	g++ ${CXXFLAGS} $< -c

clean:
	rm *.o
