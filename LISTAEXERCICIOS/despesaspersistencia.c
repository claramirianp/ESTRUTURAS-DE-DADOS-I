#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct{
	char descricao[100];
	float valor;
	char vencimento[11]; //formato dd/mm/aaaa
	int quitada;         //0 = não quitada, 1 = quitada
}Despesa;

void cadastrarDespesa(FILE* arquivo){
	Despesa nova;
	printf("Informe a Descrição: ");
	scanf(" %99[^\n]",nova.descricao);
	printf("Informe o Valor: ");
	scanf(" %f",&nova.valor);
	printf("Informe a Data de Vencimento (dd/mm/aaaa): ");
	scanf(" %10[^\n]",nova.vencimento);
	nova.quitada = 0;

	fseek(arquivo,0,SEEK_END);
	fwrite(&nova,sizeof(Despesa),1,arquivo);
	fflush(arquivo);

	printf("Despesa Cadastrada com Sucesso!\n");
}

void printDespesa(Despesa d, int posicao){
	printf("%dª Despesa\n",posicao);
	printf("Descrição: %s\n",d.descricao);
	printf("Valor: %.2f\n",d.valor);
	printf("Vencimento: %s\n",d.vencimento);
	printf("Situação: %s\n", d.quitada ? "Quitada" : "Em Aberto");
}

//retorna a quantidade de despesas no arquivo
int contarDespesas(FILE* arquivo){
	fseek(arquivo,0,SEEK_END);
	long tamanho = ftell(arquivo);
	return tamanho / sizeof(Despesa);
}

void listarDespesas(FILE* arquivo){
	int cont = contarDespesas(arquivo);
	if(cont == 0){
		printf("Nenhuma despesa cadastrada\n");
		return;
	}

	rewind(arquivo);
	Despesa d;
	int i = 1;
	while(fread(&d,sizeof(Despesa),1,arquivo) == 1){
		printDespesa(d,i);
		printf("--------------------\n");
		i++;
	}
}

void quitarDespesa(FILE* arquivo){
	int cont = contarDespesas(arquivo);
	if(cont == 0){
		printf("Nenhuma despesa cadastrada\n");
		return;
	}

	listarDespesas(arquivo);

	int posicao;
	printf("Informe a posição da despesa a ser quitada (1, 2, 3...): ");
	scanf(" %d",&posicao);

	if(posicao < 1 || posicao > cont){
		printf("Posição inválida\n");
		return;
	}

	Despesa d;
	long offset = (posicao - 1) * sizeof(Despesa);

	fseek(arquivo,offset,SEEK_SET);
	fread(&d,sizeof(Despesa),1,arquivo);

	if(d.quitada){
		printf("Essa despesa já está quitada\n");
		return;
	}

	d.quitada = 1;

	fseek(arquivo,offset,SEEK_SET);
	fwrite(&d,sizeof(Despesa),1,arquivo);
	fflush(arquivo);

	printf("Despesa Quitada com Sucesso!\n");
}

void saldoDespesas(FILE* arquivo){
	rewind(arquivo);
	Despesa d;
	float saldo = 0;

	while(fread(&d,sizeof(Despesa),1,arquivo) == 1){
		if(!d.quitada)
			saldo += d.valor;
	}

	printf("Saldo de Despesas ainda a Pagar: R$ %.2f\n",saldo);
}

FILE* abreArquivo(char nomedoarquivo[]){
	FILE* arquivo = fopen(nomedoarquivo,"rb+");
	if(!arquivo)
		arquivo = fopen(nomedoarquivo,"wb+");
	if(!arquivo)
		printf("Falha na abertura do Arquivo\nVerifique Permissões\n");
	return arquivo;
}

int interface(){
	int opcao;
	do{
		system("clear");
		printf("1 - Cadastrar Despesa\n");
		printf("2 - Listar Todas as Despesas\n");
		printf("3 - Quitar uma Despesa\n");
		printf("4 - Informar Saldo de Despesas a Pagar\n");
		printf("0 - ENCERRAR SISTEMA\n");
		printf("Informe a Opção Desejada: ");
		scanf(" %d",&opcao);
		if(opcao > 4 || opcao < 0){
			printf("Opção Inválida\n");
			continue;
		}
		break;
	}while(1);
	return opcao;
}

int main(){

	FILE* despesas = abreArquivo("despesas.dat");
	if(!despesas)
		return 1;

	do{
		switch(interface()){
			case 1: cadastrarDespesa(despesas);
					break;
			case 2: listarDespesas(despesas);
					break;
			case 3: quitarDespesa(despesas);
					break;
			case 4: saldoDespesas(despesas);
					break;
			case 0: fclose(despesas);
					return 0;
		}
		while(getchar()!='\n');
		getchar();
	}while(1);
}
