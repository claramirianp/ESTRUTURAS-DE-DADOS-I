#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INGREDIENTES 30
#define MAX_NOME 100
#define MAX_QUANTIDADE 50
#define MAX_DESCRICAO 100

typedef struct {
    char descricao[MAX_DESCRICAO];
    char quantidade[MAX_QUANTIDADE];
} Ingrediente;

typedef struct {
    char nome[MAX_NOME];
    int tempo;          // em minutos
    char dificuldade;   // F, M ou D
    int numIngredientes;
    Ingrediente ingredientes[MAX_INGREDIENTES];
} Receita;

// Array dinâmico de receitas
Receita *receitas = NULL;
int numReceitas = 0;

// Converte string para minúsculas (para busca case-insensitive)
void strToLower(char *dest, const char *src) {
    int i;
    for (i = 0; src[i]; i++) {
        dest[i] = tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

// Verifica se 'sub' está contido em 'str' (case-insensitive)
int contemSubstring(const char *str, const char *sub) {
    char strLow[MAX_NOME * 2], subLow[MAX_NOME * 2];
    strToLower(strLow, str);
    strToLower(subLow, sub);
    return strstr(strLow, subLow) != NULL;
}

int cadastrarReceita() {
    // Realoca o array para mais uma receita
    Receita *temp = realloc(receitas, (numReceitas + 1) * sizeof(Receita));
    if (temp == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return 0;
    }
    receitas = temp;

    Receita *r = &receitas[numReceitas];

    printf("\n=== CADASTRAR RECEITA ===\n");

    printf("Nome da receita: ");
    scanf(" %[^\n]", r->nome);

    printf("Tempo de preparo (minutos): ");
    scanf("%d", &r->tempo);

    char dif;
    do {
        printf("Dificuldade (F - Facil / M - Media / D - Dificil): ");
        scanf(" %c", &dif);
        dif = toupper((unsigned char)dif);
        if (dif != 'F' && dif != 'M' && dif != 'D') {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (dif != 'F' && dif != 'M' && dif != 'D');
    r->dificuldade = dif;

    int n;
    do {
        printf("Quantidade de ingredientes (1 a %d): ", MAX_INGREDIENTES);
        scanf("%d", &n);
        if (n < 1 || n > MAX_INGREDIENTES) {
            printf("Numero invalido. Tente novamente.\n");
        }
    } while (n < 1 || n > MAX_INGREDIENTES);
    r->numIngredientes = n;

    for (int i = 0; i < n; i++) {
        printf("\nIngrediente %d:\n", i + 1);
        printf("  Descricao: ");
        scanf(" %[^\n]", r->ingredientes[i].descricao);
        printf("  Quantidade: ");
        scanf(" %[^\n]", r->ingredientes[i].quantidade);
    }

    numReceitas++;
    printf("\nReceita cadastrada com sucesso!\n");
    return 1;
}

void imprimirReceita(int i) {
    Receita *r = &receitas[i];
    char dif[10];
    if (r->dificuldade == 'F') strcpy(dif, "Facil");
    else if (r->dificuldade == 'M') strcpy(dif, "Media");
    else strcpy(dif, "Dificil");

    printf("\n-----------------------------\n");
    printf("Receita: %s\n", r->nome);
    printf("Tempo:   %d minutos\n", r->tempo);
    printf("Nivel:   %s\n", dif);
    printf("Ingredientes:\n");
    for (int j = 0; j < r->numIngredientes; j++) {
        printf("  - %s: %s\n", r->ingredientes[j].descricao, r->ingredientes[j].quantidade);
    }
    printf("-----------------------------\n");
}

int consultarPorNome() {
    if (numReceitas == 0) {
        printf("Nenhuma receita cadastrada.\n");
        return 0;
    }

    char busca[MAX_NOME];
    printf("\n=== CONSULTAR POR NOME ===\n");
    printf("Digite o nome ou parte do nome: ");
    scanf(" %[^\n]", busca);

    int encontrou = 0;
    for (int i = 0; i < numReceitas; i++) {
        if (contemSubstring(receitas[i].nome, busca)) {
            imprimirReceita(i);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma receita encontrada com \"%s\".\n", busca);
        return 0;
    }
    return 1;
}

int consultarPorIngrediente() {
    if (numReceitas == 0) {
        printf("Nenhuma receita cadastrada.\n");
        return 0;
    }

    char busca[MAX_DESCRICAO];
    printf("\n=== CONSULTAR POR INGREDIENTE ===\n");
    printf("Digite o ingrediente ou parte do nome: ");
    scanf(" %[^\n]", busca);

    int encontrou = 0;
    for (int i = 0; i < numReceitas; i++) {
        for (int j = 0; j < receitas[i].numIngredientes; j++) {
            if (contemSubstring(receitas[i].ingredientes[j].descricao, busca)) {
                imprimirReceita(i);
                encontrou = 1;
                break; // evita imprimir a mesma receita mais de uma vez
            }
        }
    }

    if (!encontrou) {
        printf("Nenhuma receita encontrada com ingrediente \"%s\".\n", busca);
        return 0;
    }
    return 1;
}

int menu() {
    int opcao;
    printf("\n=============================\n");
    printf("      LIVRO DE RECEITAS      \n");
    printf("=============================\n");
    printf("1 - Cadastrar Receita\n");
    printf("2 - Consultar por Nome\n");
    printf("3 - Consultar por Ingrediente\n");
    printf("0 - Sair\n");
    printf("=============================\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    int opcao;

    do {
        opcao = menu();

        switch (opcao) {
            case 1:
                cadastrarReceita();
                break;
            case 2:
                consultarPorNome();
                break;
            case 3:
                consultarPorIngrediente();
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    free(receitas);
    return 0;
}
