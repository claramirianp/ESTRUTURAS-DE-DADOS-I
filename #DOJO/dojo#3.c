#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    int numeros[5], cont = 0;
    int acertos = 0;

    srand(time(NULL));

	printf("=========JOGO DA MEMORIA============\n");
	printf("Voce e bom para memorizar numeros? Vamos ver...\n");
    printf("A cada rodada um numero sera exibido por 1 segundo.\n");
    printf("Tente lembrar e digite o numero correto!\n");
    printf("Tecle [ENTER] para comecar...\n");
    getchar();
    system("clear");

    do {
        int aleatorio, jogador;

        // gera e armazena o numero da rodada
        aleatorio = rand() % 10;
        numeros[cont] = aleatorio;

        // exibe o numero por 1 segundo
        printf("Numero gerado: %d\n", aleatorio);
        system("sleep 1");
        system("clear");

        // jogador digita os numeros da sequencia atual
        printf("Informe os numeros que foram gerados:\n");

        int nums_jogador[cont + 1];
        int continuar = 0;

        do {
            scanf(" %d", &jogador);
            nums_jogador[continuar] = jogador;
            continuar++;
        } while (continuar < (cont + 1));

        // confere sem mostrar o gabarito
        int acertou_rodada = 1;
        for (int i = 0; i <= cont; i++) {
            if (nums_jogador[i] != numeros[i]) {
                acertou_rodada = 0;
                break;
            }
        }

        if (acertou_rodada) {
            acertos++;
        }
        system("sleep 1");
        system("clear");

        cont++;

    } while (cont < 5);

    // resultado final
    printf("=========RESULTADO=========\n\n");
    printf("Voce acertou %d de 5 rodadas!\n", acertos);
    printf("A sequencia foi:\n");
	 for (int i = 0; i < 5; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");
	
    return 0;
}
