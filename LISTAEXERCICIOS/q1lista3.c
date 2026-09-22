#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char arquitetura[20];
    char modelo_cpu[50];
    int qtd_nucleos;
    float clock_ghz;
    int ram_gb;
    int secundaria_gb;
    int possui_gpu; 
    char modelo_gpu[50];
} Computador;

void exibirRelatorio(Computador comp, int indice) {
    printf("\n--- COMPUTADOR #%d ---\n", indice + 1);
    printf("Arquitetura: %s\n", comp.arquitetura);
    printf("CPU: %s (%d Núcleos @ %.2f GHz)\n", comp.modelo_cpu, comp.qtd_nucleos, comp.clock_ghz);
    printf("Memória RAM: %d GB\n", comp.ram_gb);
    printf("Armazenamento: %d GB\n", comp.secundaria_gb);
    
    if (comp.possui_gpu == 1) {
        printf("GPU Dedicada: Sim (%s)\n", comp.modelo_gpu);
    } else {
        printf("GPU Dedicada: Não\n");
    }
    printf("-------------------------\n");
}

int main() {
    Computador lista[100]; 
    int total_cadastrado = 0;
    int num_nucleos;

    printf("=== SISTEMA DE CADASTRO DE COMPUTADORES ===\n");

    while (total_cadastrado < 100) {
        printf("\nDigite a quantidade de núcleos da CPU (ou 0 para encerrar): ");
        scanf("%d", &num_nucleos);
        
        getchar(); 

        if (num_nucleos <= 0) {
            break;
        }

        lista[total_cadastrado].qtd_nucleos = num_nucleos;

        printf("Arquitetura (ex: x64, ARM): ");
        fgets(lista[total_cadastrado].arquitetura, 20, stdin);
        lista[total_cadastrado].arquitetura[strcspn(lista[total_cadastrado].arquitetura, "\n")] = 0;

        printf("Modelo da CPU (ex: Ryzen 5): ");
        fgets(lista[total_cadastrado].modelo_cpu, 50, stdin);
        lista[total_cadastrado].modelo_cpu[strcspn(lista[total_cadastrado].modelo_cpu, "\n")] = 0;

        printf("Velocidade do Clock (GHz): ");
        scanf("%f", &lista[total_cadastrado].clock_ghz);

        printf("Espaço de Memória RAM (GB): ");
        scanf("%d", &lista[total_cadastrado].ram_gb);

        printf("Espaço de Memória Secundária (GB): ");
        scanf("%d", &lista[total_cadastrado].secundaria_gb);

        printf("Possui GPU dedicada? (1 - Sim / 0 - Não): ");
        scanf("%d", &lista[total_cadastrado].possui_gpu);
        getchar();

        if (lista[total_cadastrado].possui_gpu == 1) {
            printf("Modelo da GPU: ");
            fgets(lista[total_cadastrado].modelo_gpu, 50, stdin);
            lista[total_cadastrado].modelo_gpu[strcspn(lista[total_cadastrado].modelo_gpu, "\n")] = 0;
        } else {
            strcpy(lista[total_cadastrado].modelo_gpu, "N/A");
        }

        total_cadastrado++;
    }
    printf("\n\n=======================================\n");
    printf("       RELATÓRIO DE EQUIPAMENTOS       \n");
    printf("=======================================\n");
    
    if (total_cadastrado == 0) {
        printf("Nenhum equipamento foi cadastrado.\n");
    } else {
        for (int i = 0; i < total_cadastrado; i++) {
            exibirRelatorio(lista[i], i);
        }
    }

    return 0;
}
