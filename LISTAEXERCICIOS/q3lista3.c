#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função que gera um dia aleatório do ano (de 0 a 364)
int dt_rand_birth() {
    return rand() % 365;
}

// Função auxiliar para traduzir o índice do dia da semana para texto
const char* obterNomeDiaSemana(int diaSemana) {
    const char* dias[] = {"Domingo", "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sábado"};
    return dias[diaSemana];
}

int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    int n;
    printf("Digite o número de convidados na festa (N): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Número de convidados inválido.\n");
        return 0;
    }

    // Array para contar quantas pessoas fazem aniversário em cada um dos 365 dias do ano
    // Inicializado com zeros
    int ano[365] = {0};

    // Array para contar os aniversários por dia da semana (0 = Domingo, 1 = Segunda... 6 = Sábado)
    int diasDaSemana[7] = {0};

    // 1. Gerar as N datas aleatórias e preencher as estatísticas
    for (int i = 0; i < n; i++) {
        int diaDoAno = dt_rand_birth();
        ano[diaDoAno]++; // Adiciona uma pessoa neste dia do ano

        // Para descobrir o dia da semana, pegamos o dia do ano e tiramos o resto da divisão por 7.
        // (Isso assume hipoteticamente que o ano começou em um Domingo)
        int diaSemana = diaDoAno % 7;
        diasDaSemana[diaSemana]++;
    }

    // 2. Verificar se há pessoas que fazem aniversário no mesmo dia
    printf("\n=== VERIFICAÇÃO DE ANIVERSÁRIOS COINCIDENTES ===\n");
    int encontrouCoincidencia = 0;

    for (int i = 0; i < 365; i++) {
        if (ano[i] > 1) {
            // Se a posição tem mais de 1 pessoa, houve coincidência!
            // Para exibir de forma bonita, convertemos o índice de volta para uma estimativa de mês/dia se quiser,
            // ou apenas indicamos o número do dia do ano.
            printf("Festa garantida! %d pessoas fazem aniversário juntas no dia %d do ano.\n", ano[i], i + 1);
            encontrouCoincidencia = 1;
        }
    }

    if (!encontrouCoincidencia) {
        printf("Incrível! Ninguém faz aniversário no mesmo dia nesta festa.\n");
    }

    // 3. Descobrir qual o dia da semana com mais aniversários
    int maxAniversariosSemana = diasDaSemana[0];
    int indiceDiaMaisFrequente = 0;

    for (int j = 1; j < 7; j++) {
        if (diasDaSemana[j] > maxAniversariosSemana) {
            maxAniversariosSemana = diasDaSemana[j];
            indiceDiaMaisFrequente = j;
        }
    }

    printf("\n=== ESTATÍSTICA DOS DIAS DA SEMANA ===\n");
    printf("O dia da semana em que mais pessoas nasceram foi: %s\n", obterNomeDiaSemana(indiceDiaMaisFrequente));
    printf("Total de pessoas nascidas nesse dia da semana: %d\n", maxAniversariosSemana);

    return 0;
}
