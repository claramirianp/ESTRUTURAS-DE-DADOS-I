#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	int cartas[9],temp,troca,cont=0,partidas=0;
	srand(time(NULL));
	
	//sorteio de cartas
	for(int i=0;i<9;i++)
		cartas[i]=1+rand()%(13);
		
	//impressao cartas
	for(int i=0;i<9;i++) 
		{
		if (cartas[i]!=0)
		printf(" [%d]",cartas[i]);
		else(printf(" "));
		}
		
	do{
		//cartas ordenadas Bubble Sort
		for(int i=0;i<9;i++){
			for(int j=0;j<8;j++){
				if (cartas[j]>cartas[j+1]){
					temp=cartas[j];
					cartas[j]=cartas[j+1];
					cartas[j+1]=temp;
				}
			}
		}
		
		 //impressao ordenadas
		printf("\nCartas ordenadas:\n");
		for(int i=0;i<9;i++){
			if (cartas[i]!=0)
				printf("[%d]",cartas[i]);
		}
		//trinca
		for (int i=0;i<9;i++)
		{  
			//cartas sequenciais  
			if (cartas[i] != 0)
			{
			if ((cartas[i] == cartas[i+1]-1 && cartas[i] == cartas[i+2]-2)|| (cartas[i]== cartas[i+1] && cartas[i]==cartas[i+2]))  
			{
			printf("\nTrinca formada: [%d] [%d] [%d]\n",cartas[i],cartas[i+1],cartas[i+2]);
			cont++;
			cartas[i]=0;
			cartas[i+1]=0;
			cartas[i+2]=0;
			break;
			}
			} 
		}           
		 
		if (cont >= 3) break;
		printf("\n");
		printf("Escolha uma carta para substituir (valor):");
		scanf("%d", &troca);	
		partidas++;
		
		for (int i = 0; i < 9; i++) {
            if (cartas[i] == troca && troca != 0) {
                cartas[i] = 1 + rand() % 13; // Substitui por nova carta aleatória
                printf("Carta %d trocada com sucesso!\n", troca);
                break; // Troca apenas a primeira ocorrência encontrada
            }
        }
		
	}while (cont<3);

		printf("FIM DE JOGO!!\n");
		printf("=============RESULTADO DO JOGO===============\n"); 	//fim de jogo
		printf("Total de partidas jogadas: %d\n",partidas);
		printf("==============================================\n");
	  
	return 0;
}
