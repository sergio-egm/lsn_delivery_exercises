# This code remove any file that and as '*.o' , '*.dat' , '*.x' .
# There is the 'git' comand to remove them from the git too.
# To use it outside the git responsory remouve 'git'.

#!/bin/bash
git mv input.dat appo
git rm -rf *.dat
git mv appo input.dat
git rm -rf *.o
git rm -rf *.x