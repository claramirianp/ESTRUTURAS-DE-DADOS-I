#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main(){
		srand(time(NULL));
		char cpf[12];
		int opcao;
		do{
		printf("Selecione a opcao: 1-GERAR CPF 2-VALIDAR CPF 0-ENCERRAR\n");
		scanf("%d",&opcao);
		
		if(opcao==1){
			for(int i=0; i<9;i++){
			cpf[i]=rand()%10 +'0';}
		}
		printf("CPF: %s\n",cpf);	
		
		if(opcao==2){
			printf("Digite o CPF para validar:\n");
			
		}	
		
		int todos_iguais = 1;
		for(int i = 1; i < 11; i++) {
        if(cpf[i] != cpf[0]) {
            todos_iguais = 0;
            break;
        }
		}
		if(todos_iguais) {
        printf("ERRO: CPF invalido (todos os digitos iguais)\n");
		}	
		}while(1);
	
	return 0;
}

