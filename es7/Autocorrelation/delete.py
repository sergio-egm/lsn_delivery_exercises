import numpy as np
import os

name=input("Name of the file to shrink : ")

data=np.loadtxt(name)

lines=[]

for i in range(len(data)):
    lines.append(str(int(data[i,0]))+'\t'+str(data[i,1])+'\n')

with open(name,'w') as f:
    f.writelines(lines)
    f.close()
