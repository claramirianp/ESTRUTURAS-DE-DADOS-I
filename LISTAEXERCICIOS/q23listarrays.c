#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N, M;
    srand(time(NULL));

    printf("Digite a quantidade de pacotes (N): ");
    scanf("%d", &N);
    printf("Digite a quantidade de alunos (M): ");
    scanf("%d", &M);

    if (M >= N) {
        printf("Erro: M deve ser menor que N!\n");
        return 1;
    }

    int pacotes[N];

    // Sorteia e imprime os pacotes
    printf("\nPacotes: [");
    for (int i = 0; i < N; i++) 
    {
        pacotes[i] = rand() % 10 + 1;
        printf("%d%s", pacotes[i], i < N - 1 ? ", " : "");
    }
    printf("]\n");

    // Ordena os pacotes em ordem crescente (bubble sort)
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - i - 1; j++)
            if (pacotes[j] > pacotes[j + 1]) 
            {
                int tmp      = pacotes[j];
                pacotes[j]   = pacotes[j + 1];
                pacotes[j+1] = tmp;
            }

    printf("Pacotes ordenados: [");
    for (int i = 0; i < N; i++)
        printf("%d%s", pacotes[i], i < N - 1 ? ", " : "");
		printf("]\n");

    // Encontra a janela de M pacotes consecutivos com menor diferença
    // (pacotes[i+M-1] - pacotes[i]) é a diferença entre o maior e menor da janela
    int melhor_inicio = 0;
    int melhor_diff   = pacotes[M - 1] - pacotes[0];
    int melhor_soma   = 0;

    for (int i = 0; i < M; i++)
        melhor_soma += pacotes[i];

    for (int i = 1; i <= N - M; i++) 
    {
        int diff = pacotes[i + M - 1] - pacotes[i];
        int soma = 0;
        for (int j = i; j < i + M; j++)
            soma += pacotes[j];

        // Prefere menor diferença; em empate, prefere maior soma
        if (diff < melhor_diff || (diff == melhor_diff && soma > melhor_soma)) 
        {
            melhor_diff   = diff;
            melhor_soma   = soma;
            melhor_inicio = i;
        }
    }

    // Imprime os pacotes a distribuir
    printf("\nDistribuir pacotes contendo: ");
    for (int i = melhor_inicio; i < melhor_inicio + M; i++)
        printf("%d%s", pacotes[i], i < melhor_inicio + M - 1 ? ", " : "");
		printf("\n");
		printf("Diferenca maxima entre alunos: %d chocolate(s)\n", melhor_diff);

    return 0;
}
