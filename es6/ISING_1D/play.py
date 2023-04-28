import numpy as np
import matplotlib.pyplot as plt
import os
import subprocess

#Riscrive i parametri che voglio cambiare 
def rewrite(index,new_value,lines):
    #Controlla che l'indice sia valido
    if(index>=len(lines)):
        print("Indice non valido!\t",index)
    
    #Setta il valore nuovo
    lines[index]=str(new_value)+'\n'
    #Riscrive il file
    with open('input.dat','w') as f:
        f.writelines(lines)
        f.close()


#Valori da campionare
N=11
Tmin=0.5
Tmax=2
stepT=(Tmax-Tmin)/(N-1)

#Stampa i valori impostati
print(str(N)+" temperature misurate")
print("Intervallo di temperature ["+str(Tmin)+","+str(Tmax)+"]")
print("Lunghezza degli step "+str(stepT)+"\n")

#Legge il file originale
with open('input.dat','r') as f:
    lines=f.readlines()
    f.close()

print("FILE INIZIALE:\n")
for line in lines:
    print(line,end='')
print("\nFINE FILE INIZIALE\n")

T=np.array([Tmax-stepT*i for i in range(N)])    #Temperature da campionare

for t in T:
    rewrite(0,t,lines)
    subprocess.run(['./Monte_Carlo_ISING_1D.exe','input.dat'])
    os.system('mv output.ene.0 output_ene_'+str(np.round(t,decimals=2))+'.dat')