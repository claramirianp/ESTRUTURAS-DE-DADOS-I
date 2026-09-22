#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	int coluna, linha, aleatorio,padrao, escolha;
	int cont = 0;
	int numlinha= 20, numcoluna = 20;
	srand(time(NULL));
	
	printf("============VOCÊ É BOM DE MEMÓRIA?=======\n");
	printf("Vamos ver, você terá que descobrir qual é o numero diferente\n");
	getchar();
	system("clear");
	
	for (int i =0; i<10; i++){
		do{
			aleatorio = 1+rand() % 9;
			padrao = 1+rand() % 9;
		}while(aleatorio == padrao);
	 
	
	 linha = rand() % numlinha; 
	 coluna = rand() % numcoluna;
	 
	 for(int l =0;l<numlinha;l++){
		for(int c=0;c<numcoluna;c++){
			if(linha == l && coluna == c){
				printf(" %d", aleatorio);
				continue;
			}	
				printf(" %d",padrao);
		 }
			printf("\n");
	 }
	 
		system ("sleep 1");
		system ("clear");
		
		
		printf("VOCE ENCONTROU? ");
		scanf (" %d", &escolha);
		
		if(aleatorio == escolha){
				cont++;
			printf("Voce acertou!\n");
		}
		else{
			printf("Voce errouuuu!\n\n");
			printf ("O numero era %d\n", aleatorio);
		}
		
		while(getchar() != '\n');
		
		printf("Pressione ENTER para continuar...");
		
		getchar();
		system("clear");
		
		//numcoluna +=3;
		//numlinha +=3;
	}
	
	printf("Voce acertou %i/10\n",cont);
	return 0;
}

