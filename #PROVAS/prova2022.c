#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	int N;
	srand(time(NULL));
	
	printf("Digite o valor para N:\n");
	scanf("%d", &N);
	
	int pesos[N*N];
	int matriz[N][N];
	
	//pesos aleatorios
	for (int i=0; i<N*N; i++)
	{
		pesos[i]=rand()%20+1;
	}
	
	//bubble sort(ordenar os pesos)
	for (int i = 0; i < N * N - 1; i++) {
        for (int j = 0; j < N * N - 1 - i; j++) {
            if (pesos[j] > pesos[j + 1]) {
                int temp = pesos[j];
                pesos[j] = pesos[j + 1];
                pesos[j + 1] = temp;
            }
        }
    }
	
	//distribuicao de pesos
	 int k = 0; // índice do array de pesos
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) { // esquerda para direita
            for (int j = 0; j < N; j++)
                matriz[i][j] = pesos[k++];
        } else {           // direita para esquerda
            for (int j = N - 1; j >= 0; j--)
                matriz[i][j] = pesos[k++];
        }
    }
    
    //impressao matriz
	printf("\nDistribuicao Sugerida:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("[%02d] ", matriz[i][j]);
        printf("\n");
    }
    
    //impressao peso de cada coluna
    printf("\nPesos de Cada Coluna:\n");
    for (int j = 0; j < N; j++) {
        int soma = 0;
        for (int i = 0; i < N; i++)
            soma += matriz[i][j];
        printf("[%02d] ", soma);
    }
    printf("\n");

	return 0;
}

