#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* ──────────────────────────────────────────
   Calcula um dígito verificador do CPF
   inicio: posição inicial dos pesos
   ────────────────────────────────────────── */
int calcularDigito(const char *cpf, int inicio) {
    int soma = 0;
    int peso = inicio + 1;          /* peso começa em (inicio+1) */

    for (int i = 0; i < inicio; i++) {
        soma += (cpf[i] - '0') * peso;
        peso--;
    }

    int resto = (soma * 10) % 11;
    return (resto == 10) ? 0 : resto;
}

/* ──────────────────────────────────────────
   Gera um CPF válido como string (sem máscara)
   ────────────────────────────────────────── */
void gerarCPF(char *cpf) {
    /* Gera os 9 primeiros dígitos aleatoriamente */
    for (int i = 0; i < 9; i++)
        cpf[i] = '0' + (rand() % 10);

    /* Calcula DV1 (10º dígito) */
    cpf[9]  = '0' + calcularDigito(cpf, 9);

    /* Calcula DV2 (11º dígito) */
    cpf[10] = '0' + calcularDigito(cpf, 10);

    cpf[11] = '\0';
}

/* ──────────────────────────────────────────
   Formata CPF: "12345678909" → "123.456.789-09"
   ────────────────────────────────────────── */
void formatarCPF(const char *cpf, char *formatado) {
    sprintf(formatado, "%c%c%c.%c%c%c.%c%c%c-%c%c",
            cpf[0], cpf[1], cpf[2],
            cpf[3], cpf[4], cpf[5],
            cpf[6], cpf[7], cpf[8],
            cpf[9], cpf[10]);
}

/* ──────────────────────────────────────────
   Remove pontos e traço do CPF formatado
   ────────────────────────────────────────── */
void limparCPF(const char *entrada, char *saida) {
    int j = 0;
    for (int i = 0; entrada[i] != '\0'; i++)
        if (isdigit(entrada[i]))
            saida[j++] = entrada[i];
    saida[j] = '\0';
}

/* ──────────────────────────────────────────
   Valida CPF (string limpa, 11 dígitos)
   Retorna:
     0 → válido
    -1 → tamanho inválido
    -2 → contém caractere não numérico
    -3 → todos os dígitos são iguais
    -4 → DV1 inválido
    -5 → DV2 inválido
   ────────────────────────────────────────── */
int validarCPF(const char *cpf) {
    /* Verifica tamanho */
    if (strlen(cpf) != 11)
        return -1;

    /* Verifica se todos são dígitos */
    for (int i = 0; i < 11; i++)
        if (!isdigit(cpf[i]))
            return -2;

    /* Rejeita sequências como "00000000000" */
    int todosIguais = 1;
    for (int i = 1; i < 11; i++)
        if (cpf[i] != cpf[0]) { todosIguais = 0; break; }
    if (todosIguais)
        return -3;

    /* Verifica DV1 */
    if ((cpf[9] - '0') != calcularDigito(cpf, 9))
        return -4;

    /* Verifica DV2 */
    if ((cpf[10] - '0') != calcularDigito(cpf, 10))
        return -5;

    return 0;
}

/* ──────────────────────────────────────────
   Exibe mensagem de erro de validação
   ────────────────────────────────────────── */
void exibirErro(int codigo) {
    switch (codigo) {
        case -1: printf("  [ERRO] CPF deve ter exatamente 11 digitos.\n");    break;
        case -2: printf("  [ERRO] CPF contem caractere nao numerico.\n");     break;
        case -3: printf("  [ERRO] CPF invalido: todos os digitos sao iguais.\n"); break;
        case -4: printf("  [ERRO] Primeiro digito verificador (DV1) invalido.\n"); break;
        case -5: printf("  [ERRO] Segundo digito verificador (DV2) invalido.\n");  break;
    }
}

/* ════════════════════════════════════════════
   MENU PRINCIPAL
   ════════════════════════════════════════════ */
int main(void) {
    srand((unsigned)time(NULL));

    int opcao;
    char cpfLimpo[20];
    char cpfFormatado[20];
    char entrada[50];

    printf("╔══════════════════════════════════╗\n");
    printf("║    GERADOR E VALIDADOR DE CPF    ║\n");
    printf("╚══════════════════════════════════╝\n\n");

    do {
        printf("┌──────────────────────────────────┐\n");
        printf("│  1. Gerar CPF valido              │\n");
        printf("│  2. Validar CPF                   │\n");
        printf("│  0. Sair                          │\n");
        printf("└──────────────────────────────────┘\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        if (opcao == 1) {
            /* ── Gerar ── */
            int qtd;
            printf("Quantos CPFs deseja gerar? ");
            scanf("%d", &qtd);
            printf("\n");

            for (int i = 0; i < qtd; i++) {
                gerarCPF(cpfLimpo);
                formatarCPF(cpfLimpo, cpfFormatado);
                printf("  CPF %2d: %s  (sem mascara: %s)\n",
                       i + 1, cpfFormatado, cpfLimpo);
            }
            printf("\n");

        } else if (opcao == 2) {
            /* ── Validar ── */
            printf("Digite o CPF (com ou sem mascara): ");
            scanf("%s", entrada);

            limparCPF(entrada, cpfLimpo);
            formatarCPF(cpfLimpo, cpfFormatado);

            printf("\n  CPF informado : %s\n", entrada);
            printf("  CPF limpo     : %s\n", cpfLimpo);

            int resultado = validarCPF(cpfLimpo);

            if (resultado == 0) {
                printf("  [OK] CPF %s e VALIDO!\n\n", cpfFormatado);
            } else {
                exibirErro(resultado);
                printf("\n");
            }
        }

    } while (opcao != 0);

    printf("Encerrando...\n");
    return 0;
}
