#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    int A, B, i, leitura;
    char op;
    double resultado;

    while (1) {

        printf("Digite A operador B: ");

        leitura = scanf("%d %c %d", &A, &op, &B);

        if (leitura != 3) {
            printf("Erro: entrada invalida.\n");

            while (getchar() != '\n'); // limpa buffer
            continue;
        }

        switch(op) {

            case '+':
                resultado = A + B;
                printf("Resultado: %.2lf\n", resultado);
                break;

            case '-':
                resultado = A - B;
                printf("Resultado: %.2lf\n", resultado);
                break;

            case '*':
                resultado = A * B;
                printf("Resultado: %.2lf\n", resultado);
                break;

            case '/':

                if (B == 0) {
                    printf("Operacao nao permitida (divisao por zero).\n");
                } else {
                    resultado = (double)A / B;
                    printf("Resultado: %.2lf\n", resultado);
                }

                break;

            case '%':
                resultado = (A * B) / 100.0;
                printf("Resultado: %.2lf\n", resultado);
                break;

            case '^':
                resultado = 1;

                for (i = 0; i < B; i++) {
                    resultado *= A;
                }

                printf("Resultado: %.2lf\n", resultado);
                break;

            default:
                printf("Erro: operador invalido.\n");
        }
    }

    return 0;
}
