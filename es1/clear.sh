# This code remove any file that and as '*.o' , 'output*.dat' , '*.x' .

#!/bin/bash
git rm -rf output*.dat
git rm -rf *.o
git rm -rf *.x