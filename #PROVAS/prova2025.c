#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N;
    srand(time(NULL));

    printf("Informe a quantidade de dias no periodo:\n");
    scanf("%d", &N);

    int preco[N];

    // Gera preços aleatórios no intervalo [1, N*2]
    for (int i = 0; i < N; i++) 
    {
        preco[i] = (rand() % (N * 2)) + 1;
    }

    // a) Exibe os valores diários e o gráfico de barras
    for (int i = 0; i < N; i++) 
    {
        printf("Dia %02d: %02d  ", i + 1, preco[i]);
        for (int j = 0; j < preco[i]; j++) 
        {
            printf("_");
        }
        printf("\n");
    }

    // b) Encontra o melhor dia de compra e venda (lucro máximo)
    //    Em empate, prefere o menor intervalo (venda - compra)
    int melhor_compra = 0;
    int melhor_venda = 1;
    int melhor_lucro = preco[1] - preco[0];
    int melhor_intervalo = 1;

    for (int i = 0; i < N - 1; i++) 
    {
        for (int j = i + 1; j < N; j++) 
        {
            int lucro = preco[j] - preco[i];
            int intervalo = j - i;

            if (lucro > melhor_lucro || (lucro == melhor_lucro && intervalo < melhor_intervalo)) 
            {
                melhor_lucro     = lucro;
                melhor_compra    = i;
                melhor_venda     = j;
                melhor_intervalo = intervalo;
            }
        }
    }

    printf("\nResultado da Analise:\n");
    printf("Melhor dia para compra: Dia %02d - R$ %d\n",
           melhor_compra + 1, preco[melhor_compra]);
    printf("Melhor dia para venda:  Dia %02d - R$ %d\n",
           melhor_venda + 1, preco[melhor_venda]);
    printf("Lucro Obtido: R$ %d\n", melhor_lucro);

    return 0;
}
