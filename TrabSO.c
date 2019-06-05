#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define MAX 1000
/*-------------------------------------------------------------------------------------------*/
double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
int N; // dimensões da matriz
int T; // Numero de threads
char NomeArq[100];// nome do arquivo


/*-------------------------------------------------------------------------------------------*/
double calculaTempo(struct timespec tstart, struct timespec tend) // Calcula o tempo de execução das threads
{
  return ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
         ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
}

void *Div1(void *arg){  // Divide a matriz A e coloca a diagonal principal e acima na matriz B;
	int *pvalor;
	pvalor= arg;
	printf("Thread %i executando....\n", *pvalor);
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
	printf("Thread %i finalizada....\n", *pvalor);
}

void *Div2(void *arg){  // Divide a matriz a e coloca a diagonal principal e abaixo na matriz C;
	int *pvalor;
	pvalor= arg;
	printf("Thread %i executando....\n", *pvalor);
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
	printf("Thread %i finalizada....\n", *pvalor);

}

void *GravaMatriznoArquivo(void *arg){
	int *pvalor;
	pvalor= arg;
    FILE *saida1;
    FILE *saida2;

    saida1 = fopen("diag1.txt","w"); // imprimindo a divisão de cima
	printf("Thread %i executando....\n", *pvalor);
    for(int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
                fprintf(saida1,"%lf",B[i][j]);
        }
    }

    saida2 = fopen("diag2.txt","w"); //imprimindo a divisão de baixo

    for(int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
                fprintf(saida2,"%lf",C[i][j]);
        }
    }
printf("Thread %i finalizada....\n", *pvalor);



}

int main (){
	struct timespec tstart={0,0}, tend={0,0};
	double tempoexecucao;
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
	  clock_gettime(CLOCK_MONOTONIC, &tstart); // começo da contagem do tempo, antes das threads iniciarem sua execução

	for (i=0; i<T;i++){
		arg[i]=i+1;
		pthread_create(&threads[i], NULL,Div1,(void*)&arg[i]);
		pthread_create(&threads[i], NULL,Div2,(void*)&arg[i]);
			}
	for (i=0; i<T;i++){
		pthread_join(threads[i],NULL);
	}
	for (i=0; i<T;i++){
		arg[i]=i+1;
		pthread_create(&threads[i], NULL,GravaMatriznoArquivo,(void*)&arg[i]);
	}
	for (i=0; i<T;i++){
		pthread_join(threads[i],NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &tend); // fim da contagem do tempo, depois das threads terminarem sua execução
	tempoexecucao = calculaTempo(tstart, tend);
	printf("Tempo de execução = %.10f\n", tempoexecucao);
	printf("\n");

return 0;
}




