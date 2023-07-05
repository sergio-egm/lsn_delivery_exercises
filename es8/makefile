CXXFLG=-Wall -pedantic

compila: main.x

main.x: main.cpp main.h WaveFunction.h
	g++ ${CXXFLG} $< -o $@ -lrandom -lBlockAnalisys -lblas