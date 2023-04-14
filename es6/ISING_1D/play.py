import numpy as np
import matplotlib.pyplot as plt
import os
import subprocess

def rewrite(appo,words):
    for word in words:
        appo.writelines(word)

def comands():
    os.system('./Monte_Carlo_ISING_1D.exe')

fig,ax=plt.subplots(5,2)
rows,cols=np.shape(ax)
ax=np.reshape(ax,rows*cols)

appo=open('input.dat','r')
idk=appo.readlines()
appo.close()

numT=9
Tmin=0.5
Tmax=2
delta=(Tmax-Tmin)/numT

os.system
T=np.array([ Tmin+delta*i for i in range(numT+1) ])
for i in range(len(T)):
    pippo=open('input.dat','w')
    comands()
    idk[0]=str(T[numT-i])+'\n'
    rewrite(pippo,idk)
    pippo.close()
    data=np.loadtxt("output.ene.0")
    ax[i].plot(data[:,0],data[:,2])


plt.show()
