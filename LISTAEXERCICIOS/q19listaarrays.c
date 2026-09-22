#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	int A[10];
	int B[10];
	srand(time(NULL));
	
	for(int i=0; i<10; i++)
	{
		A[i]= rand()%100;
		B[i]= rand()%100;
	}
	
	 // --- Bubble Sort no array A ---
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9 - i; j++)
            if (A[j] > A[j + 1]) 
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }

    // --- Selection Sort no array B ---
    for (int i = 0; i < 9; i++) 
    {
        int min = i;
        for (int j = i + 1; j < 10; j++)
            if (B[j] < B[min])
                min = j;
        int temp = B[i];
        B[i] = B[min];
        B[min] = temp;
    }
    
    // Imprime os arrays ordenados
    printf("Array A (Bubble Sort):    [");
    for (int i = 0; i < 10; i++)
        printf("%d%s", A[i], i < 9 ? ", " : "");
		printf("]\n");

	printf("Array B (Selection Sort): [");
    for (int i = 0; i < 10; i++)
        printf("%d%s", B[i], i < 9 ? ", " : "");
		printf("]\n");
    
    // --- Merge sem reordenar ---
    // Percorre A e B ao mesmo tempo, sempre pegando o menor
    int C[20];
    int i = 0, j = 0, k = 0;

    while (i < 10 && j < 10) {
        if (A[i] <= B[j])
            C[k++] = A[i++];
        else
            C[k++] = B[j++];
    }

    // Copia o restante de A (se houver)
    while (i < 10)
        C[k++] = A[i++];

    // Copia o restante de B (se houver)
    while (j < 10)
        C[k++] = B[j++];

    printf("Array C (Merge):[");
    for (int x = 0; x < 20; x++)
        printf("%d%s", C[x], x < 19 ? ", " : "");
		printf("]\n");

	return 0;
}

