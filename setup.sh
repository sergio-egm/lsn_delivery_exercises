echo Setup start...
echo

echo Setup of random library:
export CPLUS_INCLUDE_PATH=$PWD/lib/random:$CPLUS_INCLUDE_PATH
echo - Included path for c++ code
export LIBRARY_PATH=$PWD/lib/random:$LIBRARY_PATH
echo - Included path for c++ compiler

echo 

echo Setup of BlockAnalisys library:
export CPLUS_INCLUDE_PATH=$PWD/lib/BlockAnalisys:$CPLUS_INCLUDE_PATH
echo - Included path for c++ code
export LIBRARY_PATH=$PWD/lib/BlockAnalisys:$LIBRARY_PATH
echo - Included path for c++ compiler

echo 
echo Setup done!
