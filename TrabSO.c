#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 1000
/*-------------------------------------------------------------------------------------------*/
double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
int N; // dimensões da matriz
int T; // Numero de threads
char NomeArq[100];// nome do arquivo


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

void GravaMatriznoArquivo(){
    FILE *saida1;
    FILE *saida2;

    saida1 = fopen("diag1.txt","w");

    for(int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
                fprintf(saida1,"%lf",B[i][j]);
        }
    }

    saida2 = fopen("diag2.txt","w");

    for(int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
                fprintf(saida2,"%lf",C[i][j]);
        }
    }




}

int main (){
	pthread_t threads[T];
	int i,j;
	int arg[T];
	FILE *diag1;


	scanf("%d %d %s",&N, &T, NomeArq); // entrada das dimensões das matrizes, o numero de threads e do arquivo.

	diag1 = fopen("diag1.txt","r");

	rename("diag1.txt", NomeArq);

	 for(i=0;i<N;i++){
        for(j=0;j<N;j++){

            fscanf(diag1,"%lf",&A[i][j]);

            }
	 }

	for (i=0; i<T;i++){
		arg[i]=i+1;
		pthread_create(&threads[i], NULL,Div1,(void*)&arg[i]);
		pthread_create(&threads[i], NULL,Div2,(void*)&arg[i]);
		pthread_join(threads[i],NULL);
	}
	printf("\n");

return 0;
}






