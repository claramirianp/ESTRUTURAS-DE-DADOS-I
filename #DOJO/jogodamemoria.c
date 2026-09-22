#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 6

int main() {
    // 3 pares: 1,1,2,2,3,3
    int cartas[TOTAL]    = {1, 1, 2, 2, 3, 3};
    int revelada[TOTAL]  = {0}; // 0 = virada, 1 = encontrada
    int pos1, pos2;
    int tentativas = 0;
    int pares_encontrados = 0;
    srand(time(NULL));

    // Embaralha as cartas
    for (int i = TOTAL - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = tmp;
    }

    printf("====== JOGO DA MEMORIA ======\n");
    printf("3 pares de cartas embaralhadas.\n");
    printf("Encontre todos os pares!\n");
    printf("Tecle [ENTER] para comecar...\n");
    getchar();
    system("clear");

    do {
        // Exibe o tabuleiro
        printf("====== JOGO DA MEMORIA ======\n\n");
        printf("Posicoes: ");
        for (int i = 0; i < TOTAL; i++) {
            printf("[%d] ", i + 1);
        }
        printf("\nCartas:   ");
        for (int i = 0; i < TOTAL; i++) {
            if (revelada[i])
                printf("    "); // carta sumiu
            else
                printf("[*] ");
        }
        printf("\n\n");
        printf("Tentativas: %d | Pares encontrados: %d de 3\n\n", tentativas, pares_encontrados);

        // Jogador escolhe a primeira carta
        do {
            printf("Escolha a primeira carta (1 a %d): ", TOTAL);
            scanf("%d", &pos1);
            pos1--; // ajusta para indice 0
            if (pos1 < 0 || pos1 >= TOTAL || revelada[pos1])
                printf("Posicao invalida ou carta ja encontrada! Tente novamente.\n");
        } while (pos1 < 0 || pos1 >= TOTAL || revelada[pos1]);

        // Mostra a primeira carta
        system("clear");
        printf("====== JOGO DA MEMORIA ======\n\n");
        printf("Posicoes: ");
        for (int i = 0; i < TOTAL; i++) printf("[%d] ", i + 1);
        printf("\nCartas:   ");
        for (int i = 0; i < TOTAL; i++) {
            if (revelada[i])
                printf("    "); // carta sumiu
            else if (i == pos1)
                printf("[%d] ", cartas[i]);
            else
                printf("[*] ");
        }
        printf("\n\n");

        // Jogador escolhe a segunda carta
        do {
            printf("Escolha a segunda carta (1 a %d): ", TOTAL);
            scanf("%d", &pos2);
            pos2--;
            if (pos2 < 0 || pos2 >= TOTAL || revelada[pos2] || pos2 == pos1)
                printf("Posicao invalida! Tente novamente.\n");
        } while (pos2 < 0 || pos2 >= TOTAL || revelada[pos2] || pos2 == pos1);

        tentativas++;

        // Mostra as duas cartas
        system("clear");
        printf("====== JOGO DA MEMORIA ======\n\n");
        printf("Posicoes: ");
        for (int i = 0; i < TOTAL; i++) printf("[%d] ", i + 1);
        printf("\nCartas:   ");
        for (int i = 0; i < TOTAL; i++) {
            if (revelada[i])
                printf("    "); // carta sumiu
            else if (i == pos1 || i == pos2)
                printf("[%d] ", cartas[i]);
            else
                printf("[*] ");
        }
        printf("\n\n");

        // Verifica se e par
        if (cartas[pos1] == cartas[pos2]) {
            printf("PAR ENCONTRADO! \n\n");
            revelada[pos1] = 1;
            revelada[pos2] = 1;
            pares_encontrados++;
        } else {
            printf("Nao e um par! Tente novamente.\n\n");
        }
        system("sleep 1");
        system("clear");

    } while (pares_encontrados < 3);

    printf("====== PARABENS! ======\n\n");
    printf("Voce encontrou todos os pares em %d tentativas!\n\n", tentativas);

    return 0;
}
