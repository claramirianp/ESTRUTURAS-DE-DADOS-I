#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

enum {PEQUENO, MEDIO, GRANDE};

typedef struct{
	char codigo[4];
	char cidade[100];
	int porte;
}Aeroporto;


typedef struct{
	Aeroporto aeroportos[100];
	int cont;
}BD_Aeroporto;


typedef struct{
	int codigo;
	char origem[4];
	char destino[4];
	int aeronave;
}Voo;

int buscar_IATA(char alvo[], Aeroporto bd[], int cont){
	for(int i=0; i<cont; i++)
		if(!strcmp(bd[i].codigo,alvo))
			return i;
	return -1;
}

Aeroporto cadastrar_Aeroporto(Aeroporto bd[], int cont){
	Aeroporto novo;
	do{
		input(STR,"Código IATA deste Aeroporto", novo.codigo);
		if(strlen(novo.codigo)!=3)
			continue;
		if(buscar_IATA(novo.codigo,bd,cont)==-1)
			break;
	}while(1);
	input(STR,"Cidade deste Aeroporto", novo.cidade);
	printf("%d - PEQUENO\n",PEQUENO);
	printf("%d - MEDIO\n",MEDIO);
	printf("%d - GRANDE\n",GRANDE);
	input(INT,"Qual Porte deste Aeroporto",&novo.porte);
	return novo;
}

void cadastar_Voo(Voo* alvo){
	
}

int interface(){
	printf("1 - Cadastrar Aeroporto\n");
	printf("2 - Listar Aeroportos\n");
	printf("3 - Cadastrar Voo\n");
	printf("4 - Listar Voos\n");
	printf("5 - Buscar Origem (Código IATA)\n");
	printf("6 - Buscar Destino (Código IATA)\n");	
	int opt;
	input(INT,"Qual Opção desejada",&opt);
	return opt;
}

void print_aeroporto(Aeroporto a){
	printf("Código IATA: %s\n",a.codigo);
	printf("Cidade: %s\n",a.cidade);
	switch(a.porte){
		case PEQUENO: printf("Porte: Pequeno\n");
					  break;
		case MEDIO: printf("Porte: Médio\n");
					  break;
		case GRANDE: printf("Porte: Grande\n");
					  break;
	};
}

void listar_aeroportos(Aeroporto lst[], int cont){
	for(int i=0; i<cont; i++)
		print_aeroporto(lst[i]);
}

int main(){
	Aeroporto bd_aero[100];
	int cont_aero = 0;
	Voo bd_voo[100];
	int cont_voo = 0;
	do{
		switch(interface()){
			case 1: bd_aero[cont_aero] = cadastrar_Aeroporto(bd_aero,cont_aero);
					cont_aero++;
					break;
			case 2: listar_aeroportos(bd_aero,cont_aero);
					break;
			case 3: cadastar_Voo(&bd_voo[cont_voo]);
					cont_voo++;
					break;
			case 4: //listar_voos(bd_voo,cont_voo);
					break;
			case 0: return 0;
		}
	}while(1);


}
