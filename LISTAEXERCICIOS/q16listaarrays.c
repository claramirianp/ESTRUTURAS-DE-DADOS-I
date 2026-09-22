#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N, X, Y;
    srand(time(NULL));

    printf("Digite N (quantidade de valores): ");
    scanf("%d", &N);
    printf("Digite X (valor minimo): ");
    scanf("%d", &X);
    printf("Digite Y (valor maximo): ");
    scanf("%d", &Y);

    if ((Y - X) <= N) {
        printf("Erro: (Y - X) deve ser maior que N!\n");
        return 1;
    }

    int arr[N];
    int sorteados = 0;

    // Sorteia N valores únicos no intervalo [X, Y]
    while (sorteados < N) {
        int num = (rand() % (Y - X + 1)) + X;

        int repetido = 0;
        for (int i = 0; i < sorteados; i++) {
            if (arr[i] == num) { repetido = 1; break; }
        }

        if (!repetido)
            arr[sorteados++] = num;
    }

    // Imprime o array sorteado
    printf("\nArray sorteado: [");
    for (int i = 0; i < N; i++)
        printf("%d%s", arr[i], i < N - 1 ? ", " : "");
    printf("]\n");

    // --- Maior sequência crescente contígua ---
    int melhor_inicio = 0, melhor_tam = 1, melhor_soma = arr[0];
    int atual_inicio = 0, atual_tam = 1, atual_soma = arr[0];

    for (int i = 1; i < N; i++) {
        if (arr[i] > arr[i - 1]) {
            // continua sequência crescente
            atual_tam++;
            atual_soma += arr[i];
        } else {
            // sequência quebrou — compara com a melhor
            if (atual_tam > melhor_tam ||
               (atual_tam == melhor_tam && atual_soma > melhor_soma)) {
                melhor_inicio = atual_inicio;
                melhor_tam    = atual_tam;
                melhor_soma   = atual_soma;
            }
            // reinicia sequência atual
            atual_inicio = i;
            atual_tam    = 1;
            atual_soma   = arr[i];
        }
    }

    // verifica última sequência
    if (atual_tam > melhor_tam ||
       (atual_tam == melhor_tam && atual_soma > melhor_soma)) {
        melhor_inicio = atual_inicio;
        melhor_tam    = atual_tam;
        melhor_soma   = atual_soma;
    }

    // Imprime a maior sequência crescente
    printf("Maior sequencia crescente: [");
    for (int i = melhor_inicio; i < melhor_inicio + melhor_tam; i++)
        printf("%d%s", arr[i], i < melhor_inicio + melhor_tam - 1 ? ", " : "");
    printf("]\n");

    return 0;
}
