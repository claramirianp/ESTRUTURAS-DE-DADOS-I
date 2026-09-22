#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    int X, Y;
    srand(time(NULL));

    printf("Digite a quantidade de LOGs existente no Server A:\n");
    scanf("%d", &X);
    printf("Digite a quantidade de LOGs existente no Server B:\n");
    scanf("%d", &Y);

    // sorteio no intervalo [0,(X+Y+1)]
    int A[X], B[Y];

    for (int i = 0; i < X; i++) {
        A[i] = rand() % (X+Y+1);
        printf("LOGs de A:[ %d ]\n", A[i]);
    }

    for (int i = 0; i < Y; i++) {
        B[i] = rand() % (X+Y+1);
        printf("LOGs de B:[ %d ]\n", B[i]);
    }

    printf("=============================================\n");
    printf("Quant. LOGs do Server A: %d\n", X);
    printf("Quant. LOGs do Server B: %d\n", Y);
    printf("=============================================\n");

    // Ordenação de A (Bubble Sort inline)
    int A_ord[X], B_ord[Y];
    for (int i = 0; i < X; i++) A_ord[i] = A[i];
    for (int i = 0; i < Y; i++) B_ord[i] = B[i];

    for (int i = 0; i < X-1; i++)
        for (int j = 0; j < X-i-1; j++)
            if (A_ord[j] > A_ord[j+1]) {
                int tmp = A_ord[j];
                A_ord[j] = A_ord[j+1];
                A_ord[j+1] = tmp;
            }

    // Ordenação de B (Bubble Sort inline)
    for (int i = 0; i < Y-1; i++)
        for (int j = 0; j < Y-i-1; j++)
            if (B_ord[j] > B_ord[j+1]) {
                int tmp = B_ord[j];
                B_ord[j] = B_ord[j+1];
                B_ord[j+1] = tmp;
            }

    // Exibir A
    printf("Server A (Obtido):  ");
    for (int i = 0; i < X; i++) printf("%d ", A[i]);
    printf("\n");

    printf("Server A (Ordenado): ");
    for (int i = 0; i < X; i++) printf("%d ", A_ord[i]);
    printf("\n");

    printf("=============================================\n");

    // Exibir B
    printf("Server B (Obtido):  ");
    for (int i = 0; i < Y; i++) printf("%d ", B[i]);
    printf("\n");

    printf("Server B (Ordenado): ");
    for (int i = 0; i < Y; i++) printf("%d ", B_ord[i]);
    printf("\n");

    printf("=============================================\n");

    // Mescla A + B ordenados e identificados
    int total = X + Y;
    int M[total];
    char origem[total];  // 'A' ou 'B'

    for (int i = 0; i < X; i++) { M[i] = A_ord[i]; origem[i] = 'A'; }
    for (int i = 0; i < Y; i++) { M[X+i] = B_ord[i]; origem[X+i] = 'B'; }

    // Ordenação da mescla mantendo origem
    for (int i = 0; i < total-1; i++)
        for (int j = 0; j < total-i-1; j++)
            if (M[j] > M[j+1]) {
                int tmp = M[j]; M[j] = M[j+1]; M[j+1] = tmp;
                char ctmp = origem[j]; origem[j] = origem[j+1]; origem[j+1] = ctmp;
            }

    printf("Mescla Server A + Server B (Ordenado e Identificado)\n");
    printf("=============================================\n");
    for (int i = 0; i < total; i++)
        printf("[%c] %d\n", origem[i], M[i]);
    printf("=============================================\n");

    return 0;
}
