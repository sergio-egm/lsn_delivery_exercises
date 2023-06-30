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
N=16
Tmin=0.5
Tmax=2
stepT=(Tmax-Tmin)/(N-1)

#Osservabili
obs=[
    "ene",
    "heat",
    "chi",
    "mag"
]

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

#Da eliminare
#if int(lines[4])+1:
#    lines[4]="1"
#    print("false")
#if int(lines[4]):
#    lines[4]="0"
#    print("true")

for t in T:
    rewrite(0,t,lines)
    subprocess.run(['./Monte_Carlo_ISING_1D.exe','input.dat'])
    for i in range(3):
        os.system('mv output.'+ obs[i] +'.0 output_'+ obs[i] +'_'+str(np.round(t,decimals=2))+'.dat')
    os.system('rm output.mag.0')

    rewrite(3,0.02,lines)
    subprocess.run(['./Monte_Carlo_ISING_1D.exe','input.dat'])
    os.system('mv output.'+ obs[3] +'.0 output_'+ obs[3] +'_'+str(np.round(t,decimals=2))+'.dat')
    os.system('rm output.*.0')

    rewrite(3,0,lines)
