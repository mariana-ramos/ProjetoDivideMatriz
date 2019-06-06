#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>


/*----------------------------VARIÁVEIS GLOBAIS------------------------------------------------*/
double **A, **B, **C;
int N; // dimensões da matriz
int T=16; // Numero de threads
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
 	char NomeFinal1 [100];
	char NomeFinal2 [100];

	strcpy(NomeFinal1, NomeArq);

	strcat(NomeFinal1,".diag1"); 
     
	saida1 = fopen(NomeFinal1,"w");

	for(int i = 0; i<N; i++){
        	for (int j = 0; j<N; j++){
                	fprintf(saida1,"%lf",B[i][j]);
        	}
    	}
	
	strcpy(NomeFinal2, NomeArq);

	strcat(NomeFinal2,".diag2");

	saida2 = fopen(NomeFinal2,"w");


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
	FILE *Arq;


	scanf("%d %d %s",&N, &T, NomeArq); // entrada das dimensões das matrizes, o numero de threads e do arquivo.

	Arq = fopen(NomeArq,"r");

/*----------------------------------------------------MATRIZES-------------------------------------------------------*/
A = (double **) malloc(N * sizeof(double *));//Alocação Matriz A
  
  
for (i=0; i<N; i++)
      A[i] = (double *) malloc(N * sizeof(double));

B = (double **) malloc(N * sizeof(double *));//Alocação Matriz B
  
  
for (i=0; i<N; i++)
      B[i] = (double *) malloc(N * sizeof(double));

C = (double **) malloc(N * sizeof(double *));//Alocação Matriz C
  
  
for (i=0; i<N; i++)
      C[i] = (double *) malloc(N * sizeof(double));
/*--------------------------------------------------------------------------------------------------------------------*/

	if(Arq == NULL){
		printf("Erro de Leitura de Arquivo\n");
	}

	else{
		for(i=0;i<N;i++){
	        for(j=0;j<N;j++){
	
	            fscanf(Arq,"%lf",&A[i][j]);

		}
	}
}
		
	 fclose(Arq);

	clock_t ini = clock();// Para calcular o tempo em segundos

	for (int i=0; i<T;i++){// Laço para criar as threads e chamar as funções de divisão
		arg[i]=i+1;
		pthread_create(&threads[i], NULL,Div1,(void*)&arg[i]);
		pthread_create(&threads[i], NULL,Div2,(void*)&arg[i]);
	}
	
	for (int i=0; i<T;i++){// Laço para criar as threads e chamar as funções de divisão
		pthread_join(threads[i],NULL);
	}
	printf("\nFuncao executou em %f segundos\n", ((double)clock() - ini) / CLOCKS_PER_SEC);
	
	GravaMatriznoArquivo();//Chama a função que faz a saída.
	printf("\n");


return 0;

}
