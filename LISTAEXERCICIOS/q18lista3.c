#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DIAS_ANO 365
#define MAX_NOME 10
#define TOTAL_ACOES 5

typedef struct {
    char nome[MAX_NOME];
    float historicoPrecos[DIAS_ANO];
} Acao;

float gerarPrecoAleatorio(float min, float max) {
    float escala = (float)rand() / (float)RAND_MAX; 
    return min + escala * (max - min);
}

void inicializarAcoes(Acao carteira[]) {
    strcpy(carteira[0].nome, "VALE3");
    strcpy(carteira[1].nome, "PETR4");
    strcpy(carteira[2].nome, "ITUB4");
    strcpy(carteira[3].nome, "BBAS3");
    strcpy(carteira[4].nome, "MGLU3");

    for (int i = 0; i < TOTAL_ACOES; i++) {
        for (int j = 0; j < DIAS_ANO; j++) {
            carteira[i].historicoPrecos[j] = gerarPrecoAleatorio(15.01f, 45.99f);
        }
    }
}

int g_nDias_valorizacao = 0;

int particionar(Acao* arr[], int baixo, int alto, int tipoCriterio) {
    Acao* pivo = arr[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        int condicao = 0;

        if (tipoCriterio == 1) {
            float varJ = ((arr[j]->historicoPrecos[0] - arr[j]->historicoPrecos[g_nDias_valorizacao]) / arr[j]->historicoPrecos[g_nDias_valorizacao]);
            float varPivo = ((pivo->historicoPrecos[0] - pivo->historicoPrecos[g_nDias_valorizacao]) / pivo->historicoPrecos[g_nDias_valorizacao]);
            condicao = (varJ > varPivo);
        } 
        else if (tipoCriterio == 2) {
            condicao = (arr[j]->historicoPrecos[0] > pivo->historicoPrecos[0]);
        } 
        else if (tipoCriterio == 3) {
            condicao = (arr[j]->historicoPrecos[0] < pivo->historicoPrecos[0]);
        }

        if (condicao) {
            i++;
            Acao* t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    Acao* t = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = t;
    return (i + 1);
}

void quicksort(Acao* arr[], int baixo, int alto, int tipoCriterio) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto, tipoCriterio);
        quicksort(arr, baixo, pi - 1, tipoCriterio);
        quicksort(arr, pi + 1, alto, tipoCriterio);
    }
}

void consultarAcao(Acao acao, int nDias) {
    if (nDias >= DIAS_ANO || nDias <= 0) {
        printf("\n[Erro] Digite um numero de dias entre 1 e %d.\n", DIAS_ANO - 1);
        return;
    }

    printf("\n=============================================\n");
    printf("ACAO: %s | Preco Atual: R$ %.2f\n", acao.nome, acao.historicoPrecos[0]);
    printf("=============================================\n");
    printf("Historico dos ultimos %d dias:\n", nDias);

    for (int i = 1; i <= nDias; i++) {
        float precoDia = acao.historicoPrecos[i];
        float precoAnterior = acao.historicoPrecos[i - 1];
        float variacaoPercentual = ((precoAnterior - precoDia) / precoDia) * 100.0f;

        printf("Dia %3d atras: R$ %5.2f | Variacao para o dia seguinte: %s%.2f%%\n", 
               i, precoDia, (variacaoPercentual >= 0 ? "+" : ""), variacaoPercentual);
    }
}

void imprimirMaioresValorizacoes(Acao carteira[], int nDias) {
    if (nDias >= DIAS_ANO || nDias <= 0) return;

    Acao* ponteiros[TOTAL_ACOES];
    for (int i = 0; i < TOTAL_ACOES; i++) ponteiros[i] = &carteira[i];

    g_nDias_valorizacao = nDias;
    quicksort(ponteiros, 0, TOTAL_ACOES - 1, 1);

    printf("\nRANKING DE VALORIZACAO NOS ULTIMOS %d DIAS (DECRESCENTE):\n", nDias);
    for (int i = 0; i < TOTAL_ACOES; i++) {
        float pAtual = ponteiros[i]->historicoPrecos[0];
        float pAntigo = ponteiros[i]->historicoPrecos[nDias];
        float var = ((pAtual - pAntigo) / pAntigo) * 100.0f;
        
        printf("%s -> Variacao: %s%.2f%% (De: R$ %.2f para R$ %.2f)\n", 
               ponteiros[i]->nome, (var >= 0 ? "+" : ""), var, pAntigo, pAtual);
    }
}

void imprimirPorPrecoMercado(Acao carteira[], int decrescente) {
    Acao* ponteiros[TOTAL_ACOES];
    for (int i = 0; i < TOTAL_ACOES; i++) ponteiros[i] = &carteira[i];

    quicksort(ponteiros, 0, TOTAL_ACOES - 1, decrescente ? 2 : 3);

    printf("\nRANKING POR PRECO DE MERCADO (%s):\n", decrescente ? "DECRESCENTE" : "CRESCENTE");
    for (int i = 0; i < TOTAL_ACOES; i++) {
        printf("%dº - %s: R$ %.2f\n", i + 1, ponteiros[i]->nome, ponteiros[i]->historicoPrecos[0]);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    Acao carteira[TOTAL_ACOES];
    inicializarAcoes(carteira);

    int opcao, nDias, idxAcao;

    do {
        printf("\n================ MENU BOLSA  ================\n");
        printf("1 - Consultar Acao Especifica (Preco, Historico e %%)\n");
        printf("2 - Ranking: Maiores Valorizacoes em N dias\n");
        printf("3 - Ranking: Maior Preco de Mercado (Decrescente)\n");
        printf("4 - Ranking: Menor Preco de Mercado (Crescente)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) return 1;

        switch (opcao) {
            case 1:
                printf("\nEscolha a acao (0 a %d):\n", TOTAL_ACOES - 1);
                for (int i = 0; i < TOTAL_ACOES; i++) {
                    printf("%d - %s\n", i, carteira[i].nome);
                }
                if (scanf("%d", &idxAcao) != 1) break;
                
                printf("Digite o numero de dias (N) para o historico: ");
                if (scanf("%d", &nDias) != 1) break;
                
                if (idxAcao >= 0 && idxAcao < TOTAL_ACOES) {
                    consultarAcao(carteira[idxAcao], nDias);
                } else {
                    printf("Acao invalida.\n");
                }
                break;
                
            case 2:
                printf("Digite o numero de dias (N) para analise de ganho: ");
                if (scanf("%d", &nDias) != 1) break;
                imprimirMaioresValorizacoes(carteira, nDias);
                break;
                
            case 3:
                imprimirPorPrecoMercado(carteira, 1);
                break;
                
            case 4:
                imprimirPorPrecoMercado(carteira, 0);
                break;
                
            case 0:
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
