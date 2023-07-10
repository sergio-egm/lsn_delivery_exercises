#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
int size, rank;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Status stat;
int itag=1;
int imesg = rank;
if(rank==1)
MPI_Send(&imesg,1,MPI_INTEGER,0,itag,MPI_COMM_WORLD);
else if(rank==0)
MPI_Recv(&imesg,1,MPI_INTEGER,1,itag,MPI_COMM_WORLD, 
&stat);
cout<<"messaggio = "<<imesg<<endl;
MPI_Finalize();
return 0;
}