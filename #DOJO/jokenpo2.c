#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PEDRA '@'
#define PAPEL '#'
#define TESOURA '%'

int main(){
	int valido;
	int pontos_pc=0;
	int pontos_user=0;
	
	do{ 
		printf(" [%c] PEDRA\n", PEDRA);
		printf(" [%c] PAPEL\n", PAPEL);
		printf(" [%c] TESOURA\n", TESOURA);

		char usuario;
		scanf (" %c", &usuario);
		int
		switch(usuario){
			case PEDRA: printf ("Pedra\n");
				break
			case PAPEL: printf ("Papel\n");
				break
			case TESOURA: printf ("Tesoura\n");
				break
			default: valido = 0;
					printf ("Símbolo inválido.\nTente novamente\n");
			}
		while(valido)
		
		char pc = rand()%3
		
		switch (pc){
			case 0: printf ("x Pedra");
				break;
			case 0: printf ("x Papel");
				break;
			case 0: printf ("x Tesoura");
				break;
			}
		if ((usuario==PEDRA && pc==0) ||
			(usuario==PAPEL && pc==1) ||
			(usuario==TESOURA && pc==2)){
			printf("Empate\n");
		}else 
			if
	}
	
	return 0;
}

