#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    int comp;
    srand(time(NULL));

    printf("=========== CORRIDA DE ASTERIX ==================\n");
    printf("Quantos competidores? ");
    scanf("%d", &comp);
    
    char nomes[comp][11];
    int posicoes[comp];
    
    // Leitura e validação dos nomes
    for (int i = 0; i < comp; i++) {
        posicoes[i] = 0;
        do {
            printf("Nome do Competidor %d: ", i + 1);
            scanf("%s", nomes[i]);
            if (strlen(nomes[i]) > 10)
                printf("Nome muito extenso! Tente novamente.\n");
        } while (strlen(nomes[i]) > 10);
    }
        
    int correndo = 1;
    
    // Loop da corrida
    while (correndo) {
        // Cada competidor avança
        for (int i = 0; i < comp; i++) {
            posicoes[i] += (rand() % 3) + 1;
        }
        
        // Atualiza a tela
        system("clear");
        printf("=========== CORRIDA DE ASTERIX ==================\n");
        for (int i = 0; i < comp; i++) {
            printf("%-10s ", nomes[i]); //- p/ alinhar o texto a esquerda
            for (int j = 0; j < posicoes[i]; j++) {
                printf("*");
            }
            printf("\n");
        }
        
        // Verifica se alguém chegou a 60
        for (int i = 0; i < comp; i++) {
            if (posicoes[i] >= 60) {
                correndo = 0; //corrida para
            }
        }
        
        if (correndo)
            system("sleep 1");
    }
    
    // Descobre o maior valor
    int maior = 0;
    for (int i = 0; i < comp; i++) {
        if (posicoes[i] > maior)
            maior = posicoes[i];
    }
    
    // Conta quantos chegaram com o maior valor
    int vencedores = 0;
    for (int i = 0; i < comp; i++) {
        if (posicoes[i] == maior)
            vencedores++;
    }
    
    printf("\n");
    if (vencedores > 1) {
        printf("HOUVE EMPATE!\n");
    } else {
        for (int i = 0; i < comp; i++) {
            if (posicoes[i] == maior)
                printf("PARABENS %s!\n", nomes[i]);
        }
    }
    
    return 0;
}
