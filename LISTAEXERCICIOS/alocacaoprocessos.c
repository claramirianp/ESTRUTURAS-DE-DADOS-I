#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PROCESSOS 100
#define TAM_NOME 50

typedef struct {
    char nome[TAM_NOME];
    char tipo[10]; 
} Processo;

Processo memoria_kernel[MAX_PROCESSOS];
Processo memoria_usuario[MAX_PROCESSOS];

int cont_kernel = 0;
int cont_usuario = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void converterParaMinusculas(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void alocarProcesso() {
    char nome[TAM_NOME];
    char tipo[10];
    
    printf("\n--- NOVO PROCESSO ---\n");
    
    printf("Nome do processo: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    printf("Tipo do processo (kernel/usuario): ");
    fgets(tipo, 10, stdin);
    tipo[strcspn(tipo, "\n")] = 0; 
    
    converterParaMinusculas(tipo);
    
    if (strcmp(tipo, "kernel") == 0) {
        if (cont_kernel < MAX_PROCESSOS) {
            strcpy(memoria_kernel[cont_kernel].nome, nome);
            strcpy(memoria_kernel[cont_kernel].tipo, "kernel");
            printf("Processo de KERNEL alocado com sucesso!\n");
            printf("Endereço: %p\n", (void*)&memoria_kernel[cont_kernel]);
            cont_kernel++;
        } else {
            printf("ERRO: Memória de kernel cheia!\n");
        }
    }
    else if (strcmp(tipo, "usuario") == 0) {
        if (cont_usuario < MAX_PROCESSOS) {
            strcpy(memoria_usuario[cont_usuario].nome, nome);
            strcpy(memoria_usuario[cont_usuario].tipo, "usuario");
            printf("Processo de USUÁRIO alocado com sucesso!\n");
            printf("Endereço: %p\n", (void*)&memoria_usuario[cont_usuario]);
            cont_usuario++;
        } else {
            printf("ERRO: Memória de usuário cheia!\n");
        }
    }
    else {
        printf("ERRO: Tipo de processo inválido! Use 'kernel' ou 'usuario'.\n");
    }
}

void exibirEstatisticas() {
    printf("\n=== ESTATÍSTICAS DOS PROCESSOS ===\n");
    printf("Total de processos armazenados: %d\n", cont_kernel + cont_usuario);
    
    printf("\n--- REGIÃO DE MEMÓRIA KERNEL ---\n");
    printf("Quantidade de processos KERNEL: %d\n", cont_kernel);
    printf("Endereço base da memória kernel: %p\n", (void*)memoria_kernel);
    printf("Tamanho da região kernel: %lu bytes\n", sizeof(Processo) * MAX_PROCESSOS);
    
    if (cont_kernel > 0) {
        printf("\nLista de processos KERNEL (com endereços):\n");
        for (int i = 0; i < cont_kernel; i++) {
            printf("  %d - Nome: %s | Endereço: %p\n", 
                   i+1, memoria_kernel[i].nome, (void*)&memoria_kernel[i]);
        }
    }
    
    printf("\n--- REGIÃO DE MEMÓRIA USUÁRIO ---\n");
    printf("Quantidade de processos USUÁRIO: %d\n", cont_usuario);
    printf("Endereço base da memória usuário: %p\n", (void*)memoria_usuario);
    printf("Tamanho da região usuário: %lu bytes\n", sizeof(Processo) * MAX_PROCESSOS);
    
    if (cont_usuario > 0) {
        printf("\nLista de processos USUÁRIO (com endereços):\n");
        for (int i = 0; i < cont_usuario; i++) {
            printf("  %d - Nome: %s | Endereço: %p\n", 
                   i+1, memoria_usuario[i].nome, (void*)&memoria_usuario[i]);
        }
    }
    
    printf("\n--- MAPA DE MEMÓRIA ---\n");
    printf("Região KERNEL: %p até %p\n", 
           (void*)memoria_kernel, 
           (void*)(&memoria_kernel[MAX_PROCESSOS - 1]));
    
    printf("Região USUÁRIO: %p até %p\n", 
           (void*)memoria_usuario, 
           (void*)(&memoria_usuario[MAX_PROCESSOS - 1]));
    
    printf("===============================\n");
}

void limparTela() {
    system("clear"); 
}

void mostrarResumo() {
    printf("\n=== RESUMO ATUAL ===\n");
    printf("Processos KERNEL: %d\n", cont_kernel);
    printf("Processos USUÁRIO: %d\n", cont_usuario);
    printf("TOTAL: %d processos\n", cont_kernel + cont_usuario);
    printf("===================\n");
}

int main() {
    int opcao;
    int computador_ligado = 1; 
    
    printf("=== SISTEMA DE GERENCIAMENTO DE PROCESSOS ===\n");
    printf("Computador ligado. Iniciando sistema...\n\n");
    
    printf("Informações de memória:\n");
    printf("Tamanho de cada processo: %lu bytes\n", sizeof(Processo));
    printf("Capacidade máxima por região: %d processos\n", MAX_PROCESSOS);
    printf("Memória total reservada: %lu bytes\n\n", 
           2 * sizeof(Processo) * MAX_PROCESSOS);
    
    while (computador_ligado == 1) {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1 - Inserir novo processo\n");
        printf("2 - Exibir estatísticas completas (com endereços)\n");
        printf("3 - Exibir resumo (apenas quantidades)\n");
        printf("4 - Limpar tela\n");
        printf("5 - Desligar computador\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        limparBuffer(); 
        
        switch(opcao) {
            case 1:
                alocarProcesso();
                break;
                
            case 2:
                exibirEstatisticas();
                break;
                
            case 3:
                mostrarResumo();
                break;
                
            case 4:
                limparTela();
                break;
                
            case 5:
                printf("\nDesligando computador...\n");
                computador_ligado = 0;
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
    
    printf("\n=== COMPUTADOR DESLIGADO ===\n");
    printf("Estatísticas finais dos processos:\n");
    exibirEstatisticas();
    printf("\nSistema finalizado. Até mais!\n");
    
    return 0;
}
