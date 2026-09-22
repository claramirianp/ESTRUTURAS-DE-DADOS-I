#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SELECOES 16

typedef struct {
    char nome[50];
    int pontos;
    int saldo;
    char grupo;
} Selecao;

int interface() {
    printf("\n= COPA DO MUNDO =\n");
    printf("1) Criar Grupo\n");
    printf("2) Informar Resultados de um Grupo\n");
    printf("3) Imprimir Classificacao Geral\n");
    printf("0) Sair\n");
    printf("Opcao: ");
    int opt;
    scanf(" %d", &opt);
    return opt;
}

int selecoesNoGrupo(Selecao copa[], int cont, char grupo) {
    int c = 0;
    for (int i = 0; i < cont; i++)
        if (copa[i].grupo == grupo)
            c++;
    return c;
}

int grupoExiste(Selecao copa[], int cont, char grupo) {
    for (int i = 0; i < cont; i++)
        if (copa[i].grupo == grupo)
            return 1;
    return 0;
}

int selecaoRepetida(Selecao copa[], int cont, char nome[]) {
    for (int i = 0; i < cont; i++)
        if (strcmp(copa[i].nome, nome) == 0)
            return 1;
    return 0;
}

int criarGrupo(Selecao copa[], int cont) {
    char nomeGrupo[10];
    printf("Nome do grupo (ex: A, B, C...): ");
    scanf(" %s", nomeGrupo);
    char grupo = nomeGrupo[0];

    if (grupoExiste(copa, cont, grupo)) {
        printf("Grupo '%c' ja existe!\n", grupo);
        return cont;
    }

    printf("Cadastre as 4 selecoes do Grupo %c:\n", grupo);
    for (int i = 0; i < 4; i++) {
        char nome[50];
        int valido = 0;
        while (!valido) {
            printf("Selecao %d: ", i + 1);
            scanf(" %[^\n]", nome);
            if (selecaoRepetida(copa, cont, nome)) {
                printf("Selecao ja cadastrada! Tente novamente.\n");
            } else {
                copa[cont].grupo = grupo;
                strcpy(copa[cont].nome, nome);
                copa[cont].pontos = 0;
                copa[cont].saldo = 0;
                cont++;
                valido = 1;
            }
        }
    }
    printf("Grupo %c criado com sucesso!\n", grupo);
    return cont;
}

int buscaSelecao(Selecao copa[], int cont, char time[]) {
    for (int i = 0; i < cont; i++)
        if (strcmp(copa[i].nome, time) == 0)
            return i;
    return -1;
}

int getSelecoesPorGrupo(Selecao copa[], int cont, char grupo, int indices[]) {
    int c = 0;
    for (int i = 0; i < cont; i++)
        if (copa[i].grupo == grupo)
            indices[c++] = i;
    return c;
}

int informarResultados(Selecao copa[], int cont) {
    char nomeGrupo[10];
    printf("Nome do grupo: ");
    scanf(" %s", nomeGrupo);
    char grupo = nomeGrupo[0];

    int indices[4];
    int qt = getSelecoesPorGrupo(copa, cont, grupo, indices);

    if (qt == 0) {
        printf("Grupo '%c' nao encontrado!\n", grupo);
        return cont;
    }

    int pares[6][2] = {
        {0,1},{0,2},{0,3},
        {1,2},{1,3},{2,3}
    };

    printf("\nInformando resultados do Grupo %c:\n", grupo);

    for (int j = 0; j < 6; j++) {
        int ia = indices[pares[j][0]];
        int ib = indices[pares[j][1]];
        int golsA, golsB;

        printf("\nJogo %d: %s x %s\n", j+1, copa[ia].nome, copa[ib].nome);

        do {
            printf("Gols de %s: ", copa[ia].nome);
            scanf(" %d", &golsA);
            if (golsA < 0) printf("Placar nao pode ser negativo!\n");
        } while (golsA < 0);

        do {
            printf("Gols de %s: ", copa[ib].nome);
            scanf(" %d", &golsB);
            if (golsB < 0) printf("Placar nao pode ser negativo!\n");
        } while (golsB < 0);

        copa[ia].saldo += (golsA - golsB);
        copa[ib].saldo += (golsB - golsA);

        if (golsA > golsB)       copa[ia].pontos += 3;
        else if (golsB > golsA)  copa[ib].pontos += 3;
        else { copa[ia].pontos += 1; copa[ib].pontos += 1; }
    }

    printf("\nResultados do Grupo %c registrados!\n", grupo);
    return cont;
}

void ordenacaoGrupo(Selecao copa[], int cont) {
    for (int i = 0; i < cont-1; i++)
        for (int j = 0; j < cont-i-1; j++)
            if (copa[j].grupo > copa[j+1].grupo) {
                Selecao troca = copa[j];
                copa[j] = copa[j+1];
                copa[j+1] = troca;
            }
}

void ordenacaoPontos(Selecao copa[], int cont) {
    for (int i = 0; i < cont-1; i++)
        for (int j = 0; j < cont-i-1; j++)
            if (copa[j].grupo == copa[j+1].grupo &&
                copa[j].pontos < copa[j+1].pontos) {
                Selecao troca = copa[j];
                copa[j] = copa[j+1];
                copa[j+1] = troca;
            }
}

void ordenacaoSaldo(Selecao copa[], int cont) {
    for (int i = 0; i < cont-1; i++)
        for (int j = 0; j < cont-i-1; j++)
            if (copa[j].grupo == copa[j+1].grupo &&
                copa[j].saldo < copa[j+1].saldo) {
                Selecao troca = copa[j];
                copa[j] = copa[j+1];
                copa[j+1] = troca;
            }
}

void classificacao(Selecao copa[], int cont) {
    if (cont == 0) {
        printf("Nenhuma selecao cadastrada!\n");
        return;
    }

    ordenacaoSaldo(copa, cont);
    ordenacaoPontos(copa, cont);
    ordenacaoGrupo(copa, cont);

    printf("\n%-30s %-6s %-6s %-6s\n", "Selecao", "Grupo", "Pts", "Saldo");
    printf("--------------------------------------------------\n");
    char grupoAtual = 0;
    for (int i = 0; i < cont; i++) {
        if (copa[i].grupo != grupoAtual) {
            grupoAtual = copa[i].grupo;
            printf("\n--- Grupo %c ---\n", grupoAtual);
        }
        printf("%-30s %-6c %-6d %-6d\n",
            copa[i].nome,
            copa[i].grupo,
            copa[i].pontos,
            copa[i].saldo);
    }
}

int main() {
    Selecao copa[MAX_SELECOES];
    int cont = 0;

    do {
        switch (interface()) {
            case 1: cont = criarGrupo(copa, cont);  
            break;
            case 2: informarResultados(copa, cont);   
            break;
            case 3: classificacao(copa, cont);        
            break;
            default: 
            return 0;
        }
    } while (1);

    return 0;
}
