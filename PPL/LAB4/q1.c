#include<mpi.h>
#include<stdio.h>
#include <stdlib.h>
#define MCW MPI_COMM_WORLD

int findFact(int n){
    int sol=1;
    for(int i=2;i<=n;i++){
        sol*=i;
    }return sol;
}

void error(int ierr){
    int errclass, resultlen;
    char err_buffer[MPI_MAX_ERROR_STRING];

    if(ierr!=MPI_SUCCESS){
        MPI_Error_class(ierr, &errclass);
        MPI_Error_string(ierr, err_buffer, &resultlen);
        fprintf(stderr,"Error class: %d-%s",errclass,err_buffer);
        MPI_Finalize();
        exit(1);
    }
}

int main(int argc, char**argv){
    int rank,size,ierr,val,f;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MCW,&rank);
    MPI_Comm_size(MCW,&size);
    MPI_Errhandler_set(MCW,MPI_ERRORS_RETURN);
    val=findFact(rank+1);
    ierr=MPI_Scan(&val,&f,1,MPI_INT,MPI_SUM,MCW);
    error(ierr);
    if(rank==size-1)
        printf("\nthe sum of factorials is:%d\n",f);
}