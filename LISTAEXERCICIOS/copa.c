#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char selecao[50];
    int pontos;
    int saldo;
    int grupo;
} Selecao;

#define NUM_GRUPOS 4
#define MAX_SELECOES (NUM_GRUPOS * 4)

int interface() {
	printf("\n================ MENU =============\n");
    printf("\n1 - Cadastrar Selecao\n2 - Classificacao\n3 - Informar Resultado\n0 - Sair\nOpcao: ");
    int opt;
    scanf(" %d", &opt);
    return opt;
}

int selecoesNoGrupo(Selecao copa[], int cont, int grupo) {
    int c = 0;
    for (int i = 0; i < cont; i++) {
        if (grupo == copa[i].grupo) 
        c++;
    }
    return c;
}

Selecao cadastrarSelecao(Selecao copa[], int cont) {
    Selecao nova;
    printf("Nome: ");
    scanf(" %[^\n]s", nova.selecao);
    nova.pontos = 0;
    nova.saldo = 0;
    int grupo;
    do {
        grupo = 'A' + rand() % NUM_GRUPOS;
        int qt_grupo = selecoesNoGrupo(copa, cont, grupo);
        if (qt_grupo < 4) break;
    } while (1);
    nova.grupo = grupo;
    printf("Selecao alocada no Grupo %c\n", nova.grupo);
    return nova;
}

void ordenacaoGrupo(Selecao copa[], int cont) {
    for (int i = 0; i < cont - 1; i++)
        for (int j = 0; j < cont - i - 1; j++)
            if (copa[j].grupo > copa[j + 1].grupo) {
                Selecao troca = copa[j];
                copa[j] = copa[j + 1];
                copa[j + 1] = troca;
            }
}

void ordenacaoPontos(Selecao copa[], int cont) {
    for (int i = 0; i < cont - 1; i++)
        for (int j = 0; j < cont - i - 1; j++)
            if (copa[j].pontos < copa[j + 1].pontos) {
                Selecao troca = copa[j];
                copa[j] = copa[j + 1];
                copa[j + 1] = troca;
            }
}

void ordenacaoSaldo(Selecao copa[], int cont) {
    for (int i = 0; i < cont - 1; i++)
        for (int j = 0; j < cont - i - 1; j++)
            if (copa[j].saldo < copa[j + 1].saldo) {
                Selecao troca = copa[j];
                copa[j] = copa[j + 1];
                copa[j + 1] = troca;
            }
}

void classificacao(Selecao copa[], int cont) {
    if (cont == 0) {
        printf("Nenhuma selecao cadastrada.\n");
        return;
    }
    ordenacaoSaldo(copa, cont);
    ordenacaoPontos(copa, cont);
    ordenacaoGrupo(copa, cont);
    printf("\n%-30s\tPts\tSG\tGrupo\n", "Selecao");
    for (int i = 0; i < cont; i++) {
        printf("%-30s\t%d\t%d\t%c\n", copa[i].selecao, copa[i].pontos, copa[i].saldo, copa[i].grupo);
    }
}

int buscaSelecao(Selecao copa[], int cont, char time[]) {
    for (int i = 0; i < cont; i++)
        if (strcmp(copa[i].selecao, time) == 0) return i;
    return -1;
}

void informarResultados(Selecao copa[], int cont) {
    if (cont < 2) {
        printf("Cadastre pelo menos 2 selecoes.\n");
        return;
    }
    char time1[50], time2[50];
    printf("Time 1: ");
    scanf(" %[^\n]s", time1);
    int localtime1 = buscaSelecao(copa, cont, time1);
    if (localtime1 == -1) {
        printf("Time nao cadastrado\n");
        return;
    }
    printf("Time 2: ");
    scanf(" %[^\n]s", time2);
    int localtime2 = buscaSelecao(copa, cont, time2);
    if (localtime2 == -1) {
        printf("Time nao cadastrado\n");
        return;
    }
    if (copa[localtime1].grupo != copa[localtime2].grupo) {
        printf("Times nao estao no mesmo grupo\n");
        return;
    }
    int placar1, placar2;
    printf("Placar %s: ", time1);
    scanf("%d", &placar1);
    printf("Placar %s: ", time2);
    scanf("%d", &placar2);
    if (placar1 > placar2) {
        copa[localtime1].pontos += 3;
        copa[localtime1].saldo += (placar1 - placar2);
        copa[localtime2].saldo -= (placar1 - placar2);
    } else if (placar2 > placar1) {
        copa[localtime2].pontos += 3;
        copa[localtime2].saldo += (placar2 - placar1);
        copa[localtime1].saldo -= (placar2 - placar1);
    } else {
        copa[localtime1].pontos += 1;
        copa[localtime2].pontos += 1;
    }
    printf("Resultado registrado!\n");
}

int main() {
    Selecao copa[MAX_SELECOES];
    int cont = 0;
    srand(time(NULL));
    do {
        switch (interface()) {
            case 1:
                if (cont < MAX_SELECOES) {
                    copa[cont] = cadastrarSelecao(copa, cont);
                    cont++;
                } else {
                    printf("Limite maximo de selecoes atingido.\n");
                }
                break;
            case 2:
                classificacao(copa, cont);
                break;
            case 3:
                informarResultados(copa, cont);
                break;
            default:
                return 0;
        }
    } while (1);
    return 0;
}
