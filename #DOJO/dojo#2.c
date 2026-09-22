#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	int pc, humano, num;
	int contpc=0, conthum=0;
	char escolha;
	
	printf("===========ADVINHE O NUMERO=========\n");
	printf("===========HUMANO VS PC=============\n");
	printf ("O PC já escolheu um numero de 0 a 99\nTente advinhá-lo o mais breve possível..\n");
	
	srand(time(NULL));
	pc=rand()%100;
	
	do{
		printf("Digite um número entre 0 e 99:\n");
		scanf(" %d",&num);
		
			if(num > pc){
				printf("O numero sorteado é MENOR que %d\n",num);
			}
			if(num < pc){
				printf("O numero sorteado é MAIOR que %d\n",num);
			}	
			conthum++;
		//while(getchar()!= '\n');
		setbuf(stdin,NULL);
		printf("Aperte ENTER para continuar\n");
		getchar();
		system("clear");
	}while(num!=pc);
	
			printf("O numero sorteado é: %d\n",pc);
			printf("A quantidade de tentativas foi de: %d\n",conthum);
			
			printf("Agora é a vez da máquina!\n");
			printf("Pressione ENTER para continuar...");
			while(getchar()!= '\n');
			getchar();
			system("clear");
			
			printf("Escolha um número para a máquina tentar adivinhar\n");
			scanf(" %d",&humano);
			
		int min=0, max=100,tentativa;			
	do{
		if(max==min)
			tentativa = min;
		else
			tentativa = min + rand()% (max-min);
			
		printf("\nA maquina chuta: %d\n", tentativa);
        printf("Digite:\n");
        printf("= (acertou)\n");
        printf("< (numero é menor)\n");
        printf("> (numero é maior)\n");
        scanf(" %c",&escolha);
		
		 if(escolha == '='){
            printf("Maquina acertou!\n");
            break;
        }
        else if(escolha == '<'){
            max = tentativa - 1;
        }
        else if(escolha == '>'){
            min = tentativa + 1;
        }
        contpc++;
		system("clear");	
	}while(tentativa!=humano);

	system("clear");
	printf("FIM DE JOGO!\n");
	printf("Pressione ENTER para continuar...\n");
	printf("A quantidade de tentativas do computador foi: %d\n",contpc);
	printf(" Tentativas pc %d  VS %d Tentativas humano",contpc,conthum);	
	return 0;
}

