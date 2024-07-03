#define _CRT_SECURE_NO_WARNINGS
#include "Graf.h"
#include "main.h"
#include "Programare.h"
#define LINE_SIZE 256

void main()
{
	Graf* g = NULL;
	FILE* pFile = fopen("Data.txt", "r");

	if (pFile)
	{
		char* token = NULL;
		char buffer[LINE_SIZE];
		char delimiter[] = ",";
		char* data_prog[LINE_SIZE];
		char* client[LINE_SIZE];
		float durata;
		char* servicii[LINE_SIZE];
		int pret;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(data_prog, token);
			token = strtok(NULL, delimiter);
			strcpy(client, token);
			token = strtok(NULL, delimiter);
			durata = atof(token);
			token = strtok(NULL, delimiter);
			strcpy(servicii, token);
			token = strtok(NULL, delimiter);
			pret = atoi(token);

			Programare* p = createProgramare(data_prog, client, durata, servicii, pret);
			//printProgramare(p);
			addEdge(&g, p);
		}

		display(g);

		int suma = valProg(g, "17.05");
		printf("Valoare: %d", suma);

		changeCost(g, "Diana", 1000);
		display(g);
		stergere(&g, 2);
		display(g);

		Stiva* stack = addStiva(g, "consult");
		printf("\n --------STIVA------\n");
		printStiva(stack);

		Coada* coada = addCoada(g, "consult");
		printf("\n --------COADA------\n");
		printCoada(coada);
		
	}
}