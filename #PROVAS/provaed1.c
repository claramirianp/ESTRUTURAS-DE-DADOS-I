#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define S 100000

int main()
{
	srand(time(NULL));
	
	int n;
	
	do
	{
	
		printf("Digite a quantidade de alunos: ");
		scanf(" %d", &n);
		if (n<=0)
		{
			system("clear");
			printf("Programa finalizado!");
			break;
		}
	
		int nasc[n];
		int cont = 0, test = 0; 
	
		for (int i = 0; i < S; i++)
			for (int j = 0; j < n; j++)
			{
				nasc[j] = 1 + rand() % 365;		
				for (int k = j - 1; k >= 0; k--)
				{
					if (nasc[j] == nasc[k])
					{
						test = 1;
						break;
					}
				}
				if (test)
				{
					test = 0;
					cont++;
					break;
				}
			}
	
		float porc = ((float)cont / S) * 100;	
		printf("Para um grupo de %d pessoas, em %.2f%% por cento dos 100K cenários foram encontrados aniversariantes na mesma data!\n", n, porc);
	
	} while (1);
	
	return 0;
}
