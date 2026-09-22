#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

typedef struct {
    int    id;
    char   titulo[100];
    char   artista[100];
    int    tempo;   // em segundos
} Musica;

Musica playlist[MAX];
int    total     = 0;   // quantidade de musicas ativas
int    proximoId = 1;   // auto-incremento

void imprimirCabecalho() {
    printf("\n%-4s  %-35s  %-20s  %s\n", "ID", "TITULO", "ARTISTA", "TEMPO");
    printf("%-4s  %-35s  %-20s  %s\n",
           "----", "-----------------------------------",
           "--------------------", "-----");
}

void imprimirMusica(Musica m) {
    int min = m.tempo / 60;
    int seg = m.tempo % 60;
    printf("%-4d  %-35s  %-20s  %d:%02d\n",
           m.id, m.titulo, m.artista, min, seg);
}

void imprimirTotalPlaylist(int segundosTotais) {
    int min = segundosTotais / 60;
    int seg = segundosTotais % 60;
    printf("\n%-4s  %-35s  %-20s  %d:%02d\n",
           "", "Tempo Total da Playlist", "", min, seg);
}

int calcularTempoTotal() {
    int soma = 0;
    for (int i = 0; i < total; i++)
        soma += playlist[i].tempo;
    return soma;
}

int adicionarMusica() {
    if (total >= MAX) {
        printf("\nPlaylist cheia! Limite de %d musicas atingido.\n", MAX);
        return 0;
    }

    Musica nova;
    nova.id = proximoId++;

    printf("\n--- Adicionar Musica (ID: %d) ---\n", nova.id);

    printf("Titulo  : ");
    scanf(" %[^\n]", nova.titulo);

    printf("Artista : ");
    scanf(" %[^\n]", nova.artista);

    printf("Tempo (segundos): ");
    scanf("%d", &nova.tempo);

    playlist[total] = nova;
    total++;

    printf("\nMusica \"%s\" adicionada com sucesso!\n", nova.titulo);
    return 1;
}

int excluirMusica() {
    if (total == 0) {
        printf("\nA playlist esta vazia.\n");
        return 0;
    }

    int idExcluir;
    printf("\nInforme o ID da musica a excluir: ");
    scanf("%d", &idExcluir);

    int pos = -1;
    for (int i = 0; i < total; i++) {
        if (playlist[i].id == idExcluir) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("\nMusica com ID %d nao encontrada.\n", idExcluir);
        return 0;
    }

    printf("\nMusica \"%s\" removida da playlist.\n", playlist[pos].titulo);

    // Compactacao do array
    for (int i = pos; i < total - 1; i++)
        playlist[i] = playlist[i + 1];

    total--;
    return 1;
}

int tocarPlaylist() {
    if (total == 0) {
        printf("\nA playlist esta vazia.\n");
        return 0;
    }

    printf("\n(Opcao 3): Tocar Playlist\n");
    imprimirCabecalho();

    for (int i = 0; i < total; i++)
        imprimirMusica(playlist[i]);

    imprimirTotalPlaylist(calcularTempoTotal());
    return 1;
}

int tocarPorArtista() {
    if (total == 0) {
        printf("\nA playlist esta vazia.\n");
        return 0;
    }

    // Copia temporaria para ordenar sem alterar a playlist original
    Musica copia[MAX];
    for (int i = 0; i < total; i++)
        copia[i] = playlist[i];

    // Bubble sort por nome do artista (depois por ID para estabilidade)
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            int cmp = strcmp(copia[j].artista, copia[j + 1].artista);
            if (cmp > 0 || (cmp == 0 && copia[j].id > copia[j + 1].id)) {
                Musica tmp  = copia[j];
                copia[j]    = copia[j + 1];
                copia[j + 1]= tmp;
            }
        }
    }

    printf("\n(Opcao 4): Tocar Playlist por Artista\n");
    imprimirCabecalho();

    for (int i = 0; i < total; i++)
        imprimirMusica(copia[i]);

    imprimirTotalPlaylist(calcularTempoTotal());
    return 1;
}

int tocarAleatorio() {
    if (total == 0) {
        printf("\nA playlist esta vazia.\n");
        return 0;
    }

    // Copia temporaria
    Musica copia[MAX];
    for (int i = 0; i < total; i++)
        copia[i] = playlist[i];

    // Fisher-Yates shuffle
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Musica tmp = copia[i];
        copia[i]   = copia[j];
        copia[j]   = tmp;
    }

    printf("\n(Opcao 5): Tocar Playlist Aleatorio\n");
    imprimirCabecalho();

    for (int i = 0; i < total; i++)
        imprimirMusica(copia[i]);

    imprimirTotalPlaylist(calcularTempoTotal());
    return 1;
}

void exibirMenu() {
    printf("\n=============================\n");
    printf("      = MINHA PLAYLIST =      \n");
    printf("=============================\n");
    printf("1) Adicionar Musica\n");
    printf("2) Excluir Musica\n");
    printf("3) Tocar Playlist (Ordem da Insercao)\n");
    printf("4) Tocar por Artista (Agrupar por Artistas)\n");
    printf("5) Tocar Aleatorio\n");
    printf("0) Sair\n");
    printf("-----------------------------\n");
    printf("Opcao: ");
}

int main() {
    srand((unsigned int)time(NULL));

    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarMusica();  break;
            case 2: excluirMusica();    break;
            case 3: tocarPlaylist();    break;
            case 4: tocarPorArtista();  break;
            case 5: tocarAleatorio();   break;
            case 0: printf("\nEncerrando playlist. Ate logo!\n"); break;
            default: printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
