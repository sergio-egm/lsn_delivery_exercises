CXXFLG=-Wall -pedantic

compila: GeneticAlgorithm.x

esegui:
	mpiexec -np 2 GeneticAlgorithm.x


%.x: %.cpp %.h
	mpicxx ${CXXFLG} $< -o $@ -lrandom
