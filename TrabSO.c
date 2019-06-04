#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 1000
/*-------------------------------------------------------------------------------------------*/
//int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
//int NumThread;
int N; // dimensões da matriz
int T; // Numero de threads 

/*-------------------------------------------------------------------------------------------*/

void *Div1(void *arg){  // Divide a matriz A e coloca a diagonal principal e acima na matriz B;
    for(int i = 0; i<N;i++){
        for(int j=0;j<N;j++){
            
            if(j>i || j==i){
                B[i][j] = A[i][j];  
            }
            else{
                B[i][j] = 0;
            }
            
        }
    }
}

void *Div2(void *arg){  // Divide a matriz a e coloca a diagonal principal e abaixo na matriz C;
	 for(int i = 0; i<N;i++){
        for(int j=0;j<N;j++){
            
            if(i>j && i!=j){
                C[i][j] = A[i][j];  
            }
            else{
                C[i][j] = 0;
            }
            
        }
    }	
	
}

int main (){
	pthread_t threads[NumThread];
	int i;
	int arg[NumThread];
	FILE *diag1;
	
	diag1 = fopen(,"r")
	
	fscanf("%d %d %s",&N, &T, &diag1); // entrada das dimensões das matrizes, o numero de threads e do arquivo.
	
	
	
	
	for (i=0; i<T;i++){
		arg[i]=i+1;
		pthread_create(&threads[i], NULL,Div1,(void*)&arg[i]);
		pthread_create(&threads[i], NULL,Div2,(void*)&arg[i]);
		pthread_join(threads[i],NULL);
	} 
	printf("\n");

	getchar();
return 0;	
}









