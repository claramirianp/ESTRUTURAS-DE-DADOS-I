#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char descricao[100];
    float valor;
    int estoque;
} Produto;

int buscar(Produto estoque[], int cont, int cod) {
    for (int i = 0; i < cont; i++)
        if (estoque[i].codigo == cod) return i;
    return -1;
}

void cadastrarProduto(Produto estoque[], int *cont) {
    if (*cont >= 100) {
        printf("Limite de produtos atingido!\n");
        return;
    }
    Produto novo;
    printf("=== CADASTRO DE PRODUTO ===\nCodigo de barras : ");
    scanf("%d", &novo.codigo);

    if (buscar(estoque, *cont, novo.codigo) != -1) {
        printf("Codigo ja cadastrado!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Descricao        : ");
    while (getchar() != '\n');
    fgets(novo.descricao, 100, stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

    printf("Valor (R$)       : ");
    scanf("%f", &novo.valor);
    printf("Estoque inicial  : ");
    scanf("%d", &novo.estoque);

    estoque[(*cont)++] = novo;
    printf("Produto cadastrado com sucesso!\n");
}

void printProduto(Produto p) {
    printf("  Codigo    : %d\n  Descricao : %s\n  Valor     : R$ %.2f\n  Estoque   : %d un\n", p.codigo, p.descricao, p.valor, p.estoque);
}

void atualizarEstoque(Produto estoque[], int cont) {
    int cod, qt;
    printf("=== ATUALIZAR ESTOQUE ===\nCodigo do produto: ");
    scanf("%d", &cod);

    int idx = buscar(estoque, cont, cod);
    if (idx == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Produto: %s | Estoque atual: %d un\nQuantidade a adicionar: ", estoque[idx].descricao, estoque[idx].estoque);
    scanf("%d", &qt);

    if (qt <= 0) {
        printf("Quantidade invalida.\n");
        return;
    }
    estoque[idx].estoque += qt;
    printf("Estoque atualizado! Novo estoque: %d un\n", estoque[idx].estoque);
}

void atualizarPreco(Produto estoque[], int cont) {
    int cod;
    float novoPreco;
    printf("=== ATUALIZAR PRECO ===\nCodigo do produto: ");
    scanf("%d", &cod);

    int idx = buscar(estoque, cont, cod);
    if (idx == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Produto: %s | Preco atual: R$ %.2f\nNovo preco (R$): ", estoque[idx].descricao, estoque[idx].valor);
    scanf("%f", &novoPreco);

    if (novoPreco <= 0) {
        printf("Preco invalido.\n");
        return;
    }
    estoque[idx].valor = novoPreco;
    printf("Preco atualizado para R$ %.2f!\n", estoque[idx].valor);
}

void venderProdutos(Produto estoque[], int cont, float *caixa) {
    if (cont == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    float totalVenda = 0;
    int cod, qt;

    printf("=== VENDA DE PRODUTOS ===\n");
    while (1) {
        printf("Codigo do produto (0 para finalizar): ");
        scanf("%d", &cod);
        if (cod == 0) break;

        int idx = buscar(estoque, cont, cod);
        if (idx == -1) {
            printf("Produto nao encontrado.\n");
            continue;
        }

        printf("Produto: %s | Preco: R$ %.2f | Estoque: %d un\nQuantidade: ", estoque[idx].descricao, estoque[idx].valor, estoque[idx].estoque);
        scanf("%d", &qt);

        if (qt <= 0 || qt > estoque[idx].estoque) {
            printf("Quantidade invalida ou estoque insuficiente!\n");
            continue;
        }

        estoque[idx].estoque -= qt;
        float subtotal = estoque[idx].valor * qt;
        totalVenda += subtotal;
        printf("Adicionado! Subtotal: R$ %.2f\n", subtotal);
    }

    if (totalVenda > 0) {
        *caixa += totalVenda;
        printf("----------------------------------------\nTOTAL DA VENDA : R$ %.2f\nVenda concluida com sucesso!\n", totalVenda);
    } else {
        printf("Nenhum item vendido.\n");
    }
}

void sangriaCaixa(float *caixa) {
    float valor;
    printf("=== SANGRIA DE CAIXA ===\nSaldo atual: R$ %.2f\nValor da sangria (R$): ", *caixa);
    scanf("%f", &valor);

    if (valor <= 0 || valor > *caixa) {
        printf("Valor invalido ou maior que o saldo!\n");
        return;
    }
    *caixa -= valor;
    printf("Sangria realizada! Novo saldo: R$ %.2f\n", *caixa);
}

void relatorioProdutos(Produto estoque[], int cont) {
    printf("=== RELATORIO DE PRODUTOS ===\n");
    if (cont == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    for (int i = 0; i < cont; i++) {
        printf("----------------------------------------\n");
        printProduto(estoque[i]);
    }
    printf("----------------------------------------\nTotal cadastrado: %d produto(s)\n", cont);
}

int menu() {
    int opcao;
    do {
        system("clear");
        printf("========================================\n        SISTEMA DE MERCEARIA            \n========================================\n");
        printf("  1 - Cadastrar Produto\n  2 - Relatorio de Produtos\n  3 - Atualizar Estoque\n  4 - Atualizar Preco\n  5 - Vender Produtos\n  6 - Sangria de Caixa\n  0 - Encerrar Sistema\n========================================\n  Opcao: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 6);
    return opcao;
}

int main() {
    Produto estoque[100];
    int cont = 0, op;
    float caixa = 0;

    do {
        op = menu();
        if (op == 1) cadastrarProduto(estoque, &cont);
        else if (op == 2) relatorioProdutos(estoque, cont);
        else if (op == 3) atualizarEstoque(estoque, cont);
        else if (op == 4) atualizarPreco(estoque, cont);
        else if (op == 5) venderProdutos(estoque, cont, &caixa);
        else if (op == 6) sangriaCaixa(&caixa);
        else if (op == 0) {
            printf("Caixa final: R$ %.2f\nSistema encerrado.\n", caixa);
            return 0;
        }
        printf("\nPressione ENTER para continuar...");
        while (getchar() != '\n');
        getchar();
    } while (1);
}
