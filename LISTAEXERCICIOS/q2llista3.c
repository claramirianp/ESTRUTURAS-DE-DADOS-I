#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main() {
    // Inicializa o gerador de números aleatórios com base no tempo atual
    srand(time(NULL));

    Horario horarios[10];
    
    // 1. Preenche o array com 10 horários aleatórios e imprime
    printf("=== HORÁRIOS GERADOS ALEATORIAMENTE ===\n");
    for (int i = 0; i < 10; i++) {
        horarios[i] = dt_rand_time();
        printf("[%d] %02d:%02d:%02d\n", i + 1, horarios[i].hora, horarios[i].minuto, horarios[i].segundo);
    }

    // 2. Obtém e imprime a hora atual do sistema
    Horario atual = dt_get_current_time();
    printf("\n=======================================\n");
    printf("Hora Atual do Sistema: %02d:%02d:%02d\n", atual.hora, atual.minuto, atual.segundo);
    printf("=======================================\n\n");

    int segundosAtual = horarioParaSegundos(atual);

    // Variáveis para guardar o melhor candidato do passado e do futuro
    Horario passadoMaisProximo;
    Horario futuroMaisProximo;
    
    // Iniciamos com distâncias absurdamente grandes (24h em segundos é 86400)
    int menorDistanciaPassado = 999999; 
    int menorDistanciaFuturo = 999999;
    
    int achouPassado = 0;
    int achouFuturo = 0;

    // 3. Varredura do array para encontrar os mais próximos
    for (int i = 0; i < 10; i++) {
        int segundosItem = horarioParaSegundos(horarios[i]);
        int diferenca = segundosItem - segundosAtual;

        if (diferenca < 0) { 
            // O horário do array é MENOR que o atual -> PASSADO
            int dist = -diferenca; // Torna o número positivo
            if (dist < menorDistanciaPassado) {
                menorDistanciaPassado = dist;
                passadoMaisProximo = horarios[i];
                achouPassado = 1;
            }
        } else { 
            // O horário do array é MAIOR ou IGUAL ao atual -> FUTURO
            if (diferenca < menorDistanciaFuturo) {
                menorDistanciaFuturo = diferenca;
                futuroMaisProximo = horarios[i];
                achouFuturo = 1;
            }
        }
    }

    // 4. Exibe os resultados (Simulação de alertas de compromisso)
    if (achouPassado) {
        printf("🚨 Último Compromisso (Passado mais próximo): %02d:%02d:%02d\n", 
               passadoMaisProximo.hora, passadoMaisProximo.minuto, passadoMaisProximo.segundo);
    } else {
        printf("🚨 Último Compromisso: Nenhum horário anterior encontrado no array.\n");
    }

    if (achouFuturo) {
        printf("📅 Próximo Compromisso (Futuro mais próximo):  %02d:%02d:%02d\n", 
               futuroMaisProximo.hora, futuroMaisProximo.minuto, futuroMaisProximo.segundo);
    } else {
        printf("📅 Próximo Compromisso: Nenhum horário futuro encontrado no array.\n");
    }

    return 0;
}
