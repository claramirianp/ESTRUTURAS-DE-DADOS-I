#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	char escolha;
	int pc, user, empate = 0, ppc=0 , puser=0;
	srand(time(NULL));
	
	for (int i=0; i<5; i++){
		
		printf("\n=========JOKENPO==========\n");
		printf("(@)PEDRA\n(%%)PAPEL\n(#)TESOURA\n");
		scanf(" %c", &escolha);
		
		pc = 1+rand()%3;

	
		switch (escolha){
			case '@':
			user = 1;
			break;
			
			case '%':
			user = 2;
			break;
			
			case '#':
			user = 3;
			break;
		}
		printf("SUA ESCOLHA FOI:%c\n", escolha);
		
		printf ("ESCOLHA DO PC:" );

		switch (pc){
			case 1:
			putchar('@');
			break;
			
			case 2:
			putchar ('%');
			break;
			
			case 3:
			putchar('#');
			break;
		}
			
		
		if (user == pc){
			printf ("\nEMPATE!\n");
			empate = empate+1;
		}
		else if (( user == 1 && pc == 2 )||( user == 2 && pc == 3) ||( user == 3 && pc == 1)) {
			printf ("\nPC GANHOU!");
			ppc = ppc+1;
			}
		else {
			printf("\nO JOGADOR GANHOU!\n");
			puser = puser+1;
			}

	}
			while(getchar() != '\n');

		printf ("PONTUACAO:\nPC:%d\nUSER:%d\nEMPATE:%d\n",ppc,puser,empate);
		
		if (ppc > puser){
			printf ("PC VENCEU!");
			}
			else if ( puser > ppc){
				printf ("USER VENCEU!");
				}
			else{
				printf("EMPATE");
				}

	return 0;
}

