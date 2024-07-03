#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "produs.h"
#define  LINE_SIZE 256
#include "Arbore.h"

void main()
{
	Arbore* root = NULL;
	
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char* token = NULL;
		char delimiter[] = ",";
		char buffer[LINE_SIZE];
		unsigned short int id;
		char* denumire[LINE_SIZE];
		unsigned short int stoc;
		unsigned char nr_clienti;
		unsigned short int* stocuri_clienti;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			id = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(denumire, token);
			token = strtok(NULL, delimiter);
			stoc = atoi(token);
			token = strtok(NULL, delimiter);
			nr_clienti = atoi(token);
			
			stocuri_clienti = (unsigned short int*)malloc(sizeof(unsigned short int) * nr_clienti);
			for (int i = 0; i < nr_clienti; i++)
			{

				token = strtok(NULL, ",");

				if(token)
					stocuri_clienti[i] = atoi(token);
			}

			Produs* p = createProdus(id, denumire, stoc, nr_clienti, stocuri_clienti);
			//printProdus(p);

			upsert(&root, p);
		}
		inordine(root);

		int count = countProduse(&root, 20);
		printf("\nnr prod: %d\n", count);

		//float medie = stocMediu(&root, 3);
		//printf("\nVal medie: %d\n", medie);

		deleteRadacina(&root, &(root)->right);
		inordine(root);

		printf("\n\n");
		Lista* list = NULL;

		createLista(root, 3, &list);
		afisareLista(list);
	}
}