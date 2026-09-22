#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int codigo;
    char descricao[100];
    float valor;
    int estoque;
} Produto;

//cadastrar struct
//passagem de parametro por REFERENCIA
//retorno de funcao

/*void cadastrarProduto(Produto* p){
		printf("Informe o codigo de barras: ");
		scanf("%d",&p->codigo);
		printf("Informe a Descricao: ");
		scanf("%d",p->descricao);
		printf("Informe o Valor: ");
		scanf("%d",&p->valor);
		printf("Informe o Estoque Disponivel: ");
		scanf("%d",&p->estoque);
		printf("Item Cadastrado com Sucesso...ENTER para continuar\n");
}*/
Produto cadastrarProduto(){
	Produto novo;
	printf("Informe o codigo de barras: ");
	scanf("%d",&novo.codigo);
	printf("Informe a Descricao: ");
	scanf("%s",novo.descricao);
	printf("Informe o Valor: ");
	scanf("%f",&novo.valor);
	printf("Informe o Estoque Disponivel: ");
	scanf("%d",&novo.estoque);
	printf("Item Cadastrado com Sucesso...ENTER para continuar\n");
	return novo;
}

void printProduto(Produto prod) {       
    printf("Código: %d\n", prod.codigo);
    printf("Descrição: %s\n", prod.descricao);
    printf("Valor: %.2f\n", prod.valor);  
    printf("Estoque: %d\n", prod.estoque); 
}                                          

void venderProduto(Produto *p, int qt) {   
    if (p->estoque < qt) {
        printf("Qtde deste Item não está Disponível.\n");
        return;
    }
    p->estoque -= qt;
    printf("Venda Realizada com Sucesso.\n");
}
int interface(){
	int opcao;
	do{
		system ("clear");
		printf("1-Cadastrar produtos\n");
		printf("2-Listar produtos\n");
 		printf("3-Consultar produtos\n");
		printf("4-Vender um produtos\n");
		printf("5-Atualizar estoque\n");
		printf("6-Fechamento de Caixa\n");
		printf("0- ENCERRAR SISTEMA\n");
		scanf("%d",&opcao);
			if (opcao >6 || opcao < 0){
				printf("Opcao Invalida!\n");
				continue;
				}
	}while(opcao > 6 || opcao < 0);
	return opcao;
}
int main() {
	//representa a base de dados das entidades
	Produto estoque[100];
	int cont=0;
	
   do{
	  switch (interface()){
		  case 1:estoque[cont] = cadastrarProduto();
					cont++;
		  break;
		  case 2:for (int i=0; i<cont; i++)
					printProduto(estoque[i]);
		  break;
		  case 3: for (int i = 0; i < cont; i++) {
                    if (estoque[i].codigo == cod) {
                        printProduto(estoque[i]);
		 break;
		/*  case 4:;
		  break;
		  case 5:;
		  break;
		*/
		  case 0:printf("Encerrando sistema...\n");
				return 0;
		  }
		 while(getchar()!= '\n');
		 getchar();
	   }while(1);
    return 0;
}
