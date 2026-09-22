#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N, X, Y;
    srand(time(NULL));

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &N);
    printf("Valor minimo X: ");
    scanf("%d", &X);
    printf("Valor maximo Y: ");
    scanf("%d", &Y);

    int vet[N];

    // Sorteia os valores
    printf("\nArray sorteado: [");
    for (int i = 0; i < N; i++) 
    {
        vet[i] = (rand() % (Y - X + 1)) + X;
        printf("%d%s", vet[i], i < N - 1 ? ", " : "");
    }
    printf("]\n");

    // Conta a frequência de cada valor no intervalo [X, Y]
    int tamanho = Y - X + 1;
    int freq[tamanho];

    for (int i = 0; i < tamanho; i++)
        freq[i] = 0;

    for (int i = 0; i < N; i++)
        freq[vet[i] - X]++;

    // Ordena por frequência (decrescente) usando bubble sort
    // Trabalha com pares: valor e frequência
    int valores[tamanho], freqs[tamanho];
    int total = 0;

    // Só considera valores que apareceram ao menos 1 vez
    for (int i = 0; i < tamanho; i++)
    {
        if (freq[i] > 0) 
        {
            valores[total] = X + i;
            freqs[total]   = freq[i];
            total++;
        }
    }

    // Bubble sort por frequência decrescente
    for (int i = 0; i < total - 1; i++) 
    {
        for (int j = 0; j < total - i - 1; j++)
        {
            if (freqs[j] < freqs[j + 1])
            {
                // troca frequência
                int tmp  = freqs[j];
                freqs[j] = freqs[j + 1];
                freqs[j + 1] = tmp;
                // troca valor junto
                tmp        = valores[j];
                valores[j] = valores[j + 1];
                valores[j + 1] = tmp;
            }
        }
    }

    // Imprime ordenado por frequência
    printf("Ordenado por frequencia: ");
    for (int i = 0; i < total; i++)
        for (int j = 0; j < freqs[i]; j++)
            printf("%d ", valores[i]);
    printf("\n");

    // Imprime tabela de frequências
    printf("\nValor | Frequencia\n");
    printf("------+-----------\n");
    for (int i = 0; i < total; i++)
        printf("  %3d |  %d\n", valores[i], freqs[i]);

    return 0;
}
