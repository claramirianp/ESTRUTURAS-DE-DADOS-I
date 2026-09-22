#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char entrada[100];
    int cartao[16];

    printf("Digite o numero do cartao: ");
    scanf("%s", entrada);

    // RESTRICAO #01 - Verificar se tem exatamente 16 digitos numericos
    if (strlen(entrada) != 16) {
        printf("Falha na Leitura do Cartao\n");
        return 0;
    }
    for (int i = 0; i < 16; i++) {
        if (entrada[i] < '0' || entrada[i] > '9') {
            printf("Falha na Leitura do Cartao\n");
            return 0;
        }
        cartao[i] = entrada[i] - '0'; // converte char para inteiro
    }

    // RESTRICAO #02 - Verificar bandeira pelo primeiro digito
    char *bandeira;
    if (cartao[0] == 3) {
        bandeira = "American Express";
    } else if (cartao[0] == 4) {
        bandeira = "Visa";
    } else if (cartao[0] == 5) {
        bandeira = "MasterCard";
    } else {
        printf("Cartao de Credito Recusado\n");
        return 0;
    }

    // RESTRICAO #03 - Checksum (algoritmo de Luhn)
    int soma = 0;
    for (int i = 0; i < 16; i++) {
        int valor;
        if (i % 2 == 0) {
            // Grupo 1: posicoes pares, multiplicar por 2
            valor = cartao[i] * 2;
            if (valor > 9) {
                valor = (valor / 10) + (valor % 10); // soma os digitos
            }
        } else {
            // Grupo 2: posicoes impares, valor original
            valor = cartao[i];
        }
        soma += valor;
    }

    if (soma % 10 != 0) {
        printf("Cartao de Credito Invalido\n");
        return 0;
    }

    // Cartao valido!
    printf("Cartao Valido!\n");
    printf("Bandeira: %s\n", bandeira);
    printf("Soma de Verificacao: %d\n", soma);

    return 0;
}
