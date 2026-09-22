#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
	int codigoBarras;
	char descricao[100];
	float valor;
	int estoque;
}Produto;


//cadastrar produtos
	//exit para interromper
//fase de vendas
	//ler um codigo de barras
	//verificar se existe
	//se existe, imprimir os dados do produto
	//ler a qtde de itens
	//verificar se possui estoque
	//calcular sub-total
	//repetir ação até codigo de barras < 0
	//total da venda
	//valor pago
	//troco a ser entregue
