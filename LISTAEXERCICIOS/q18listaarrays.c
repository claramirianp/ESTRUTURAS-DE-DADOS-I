#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N;
    srand(time(NULL));

    printf("Digite a quantidade de artigos a ser analisados:\n");
    scanf("%d", &N);

    int citacoes[N];
    for (int i = 0; i < N; i++) {
        citacoes[i] = rand() % (N + 1);
        printf("Artigo %d, citado: %d\n", i + 1, citacoes[i]);
    }

    // Conta quantos artigos tiveram mais de 4 citações
    int h = 0;
    for (int i = 0; i < N; i++) {
        if (citacoes[i] >= 4)
            h++;
    }
	printf("h-index:%d\n",h);
    printf("Existem pelo menos %d artigos com mais de 4 citacoes.\n", h);

    return 0;
}
