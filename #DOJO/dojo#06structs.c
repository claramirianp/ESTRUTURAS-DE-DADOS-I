#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define max_nome [10];

typedef struct{
	int nome[max_nome];
	int comp;
	char carac[100];
} Participante;

int main(){
	srand(time(NULL));
	int quant;
	int posicoes[comp];

	printf("==============CHAR RACE===============\n");
	printf("Digite a quantidade de participantes:\n");
	scanf("%d",&comp);
	getchar();
	
	printf("Digite o símbolo do participante:\n");
	scanf("%c",&carac);
	
	for(int i=0 i<comp;i++)
	{
		posicoes[i]=0;
		 do {
            printf("Nome do Competidor %d: ", i + 1);
            scanf("%s", nomes[i]);
            if (strlen(nomes[i]) > 10)
                printf("Nome muito extenso! Tente novamente.\n");
        } while (strlen(nomes[i]) > 10);

	}
	return 0;
}

