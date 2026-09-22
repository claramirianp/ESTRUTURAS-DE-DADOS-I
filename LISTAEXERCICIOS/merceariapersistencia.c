#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NAOEXISTE -1
#define MAX 1000

//definindo o(s) modelo(s) que meu sw necessita!
typedef struct{
	int codigo;
	char descricao[100];
	float valor;
	int estoque;
}Produto;

void cadastrarProduto(FILE* estoque){
	Produto novo;
	printf("Informe o Código de Barras: ");
	scanf(" %d",&novo.codigo);
	printf("Informe a Descrição: ");
	scanf(" %99[^\n]",novo.descricao);
	printf("Informe o Valor: ");
	scanf(" %f",&novo.valor);
	printf("Informe o Estoque Disponível: ");
	scanf(" %d",&novo.estoque);

	//posiciona no final do arquivo e grava um novo registro
	fseek(estoque,0,SEEK_END);
	fwrite(&novo,sizeof(Produto),1,estoque);
	fflush(estoque);

	printf("Item Cadastrado com Sucesso. ENTER para continuar...");
}

void printProduto(Produto prod){
	printf("Código: %d\n",prod.codigo);
	printf("Descrição: %s\n",prod.descricao);
	printf("Valor: %.2f\n",prod.valor);
	printf("Estoque: %d\n",prod.estoque);
}

void venderProduto(Produto *p, int qt){
	if(p->estoque < qt){
		printf("Qtde deste Item não está Disponível\n");
		return;
	}
	p->estoque -= qt;
	printf("Venda Realizada com Sucesso\n");
}

//essa função irá simular a camada de Visão!
int interface(){
	int opcao;
	do{
		system("clear");
		printf("1 - Cadastrar Produto\n");
		printf("2 - Listar Produtos Ordenados por Nome\n");
		printf("3 - Consultar um Produto\n");
		printf("4 - Vender Produtos\n");
		printf("5 - Atualizar Estoque de Produto\n");
		printf("6 - Fechamento de Caixa\n");
		printf("0 - ENCERRAR SISTEMA\n");
		printf("Informe a Opção Desejada: ");
		scanf(" %d",&opcao);
		if(opcao > 6 || opcao < 0){
			printf("Opção Inválida\n");
			continue;
		}
		break;
	}while(1);
	return opcao;
}

void ordenarEstoquePorDescricao(Produto estoque[],int cont){
	for(int i=0;i<cont-1;i++){
		for(int j=0;j<cont-i-1;j++){
			if(strcmp(estoque[j].descricao,estoque[j+1].descricao) > 0){
				Produto temp = estoque[j];
				estoque[j] = estoque[j+1];
				estoque[j+1] = temp;
			}
		}
	}
}

//lê o arquivo inteiro pra uma lista temporária só pra poder ordenar e exibir
//não altera nada em disco
void imprimirEstoque(FILE* estoque){
	Produto vet[MAX];
	int cont = 0;

	rewind(estoque);
	while(cont < MAX && fread(&vet[cont],sizeof(Produto),1,estoque) == 1)
		cont++;

	if(cont == 0){
		printf("Nenhum produto cadastrado\n");
		return;
	}

	ordenarEstoquePorDescricao(vet,cont);

	for(int i=0;i<cont;i++){
		printProduto(vet[i]);
		printf("--------------------\n");
	}
}

//busca no arquivo, registro por registro. Se achar, devolve a posição (índice)
//do registro e preenche *out com os dados dele
int localizarProduto(FILE* estoque, int cod, Produto *out){
	rewind(estoque);
	Produto p;
	int i = 0;
	while(fread(&p,sizeof(Produto),1,estoque) == 1){
		if(p.codigo == cod){
			if(out) *out = p;
			return i;
		}
		i++;
	}
	return NAOEXISTE;
}

int consultarProduto(FILE* estoque){
	int cod;
	printf("informe código \n");
	scanf(" %d", &cod);

	Produto p;
	int i = localizarProduto(estoque,cod,&p);
	if(i == NAOEXISTE){
		printf("Esse produto não Existe\n");
		return NAOEXISTE;
	}
	printProduto(p);
	return i;
}

void atualizarEstoque(FILE* estoque){
	int i = consultarProduto(estoque);
	if(i == NAOEXISTE)
		return;

	int n;
	printf("Informe o novo estoque\n");
	scanf(" %d", &n);

	Produto p;
	//volta pro registro exato (i-ésima posição) pra ler e regravar só ele
	fseek(estoque, i*sizeof(Produto), SEEK_SET);
	fread(&p,sizeof(Produto),1,estoque);
	p.estoque = n;

	fseek(estoque, i*sizeof(Produto), SEEK_SET);
	fwrite(&p,sizeof(Produto),1,estoque);
	fflush(estoque);

	printf("Estoque Atualizado com Sucesso\n");
}

float venderProdutos(FILE* estoque){
	int cod, qt;
	printf("Informe o código do produto: ");
	scanf(" %d",&cod);

	Produto p;
	int i = localizarProduto(estoque,cod,&p);
	if(i == NAOEXISTE){
		printf("Esse produto não Existe\n");
		return 0;
	}
	printProduto(p);

	printf("Informe a quantidade desejada: ");
	scanf(" %d",&qt);

	int estoqueAntes = p.estoque;
	venderProduto(&p,qt);
	int vendido = estoqueAntes - p.estoque;

	if(vendido > 0){
		fseek(estoque, i*sizeof(Produto), SEEK_SET);
		fwrite(&p,sizeof(Produto),1,estoque);
		fflush(estoque);
	}

	return vendido * p.valor;
}

FILE* abreArquivo(char nomedoarquivo[]){
	FILE* arquivo = fopen(nomedoarquivo,"rb+");
	if(!arquivo)
		arquivo = fopen(nomedoarquivo,"wb+");
	if(!arquivo)
		printf("Falha na abertura do Arquivo\nVerifique Permissões\n");
	return arquivo;
}

int main(){

	FILE* estoque = abreArquivo("produtos.dat");
	//FILE* fornecedores = abreArquivo("fornecedores.dat");
	//FILE* nfe = abreArquivo("nfe.dat");
	//FILE* clientes = abreArquivo("clientes.dat");

	if(!estoque)
		return 1;

	float caixa = 0;

	do{
		switch(interface()){
			case 1: cadastrarProduto(estoque);
					break;
			case 2: imprimirEstoque(estoque);
					break;
			case 3: consultarProduto(estoque);
					break;
			case 4: caixa += venderProdutos(estoque);
					break;
			case 5: atualizarEstoque(estoque);
					break;
			case 6: printf("Fechamento de Caixa: R$ %.2f\n", caixa);
					break;
			case 0: fclose(estoque);
					return 0;
		}
		while(getchar()!='\n');
		getchar();
	}while(1);
}
