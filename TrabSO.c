#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 1000

/*----------------------------VARIÁVEIS GLOBAIS------------------------------------------------*/
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
printf("B existe\n");
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
printf("C existe\n");
}

void GravaMatriznoArquivo(){
    FILE *saida1;
    FILE *saida2;

    saida1 = fopen("AAAA.txt","w");

    for(int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
                fprintf(saida1,"%lf",B[i][j]);
        }
    }

    saida2 = fopen("BBBB.txt","w");

    for(int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
                fprintf(saida2,"%lf",C[i][j]);
        }
    }

printf("Arquivos gravados se Deus quiser\n");


}

int main (){
	pthread_t threads[T];
	int i,j;
	int arg[T];
	FILE *Arq;


	scanf("%d %d %s",&N, &T, NomeArq); // entrada das dimensões das matrizes, o numero de threads e do arquivo.

	Arq = fopen(NomeArq,"r");


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

	for (int i=0; i<T/2;i++){// Laço para criar as threads e chamar a função Div1
		arg[i]=i+1;
		pthread_create(&threads[i], NULL,Div1,(void*)&arg[i]);
		pthread_create(&threads[i], NULL,Div2,(void*)&arg[i]);
		pthread_join(threads[i],NULL);
	}
	
	GravaMatriznoArquivo();//Chama a função que faz a saída.
	printf("\n");

return 0;
}
