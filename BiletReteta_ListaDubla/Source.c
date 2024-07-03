#define _CRT_SECURE_NO_WARNINGS
#include "Reteta.h"
#include "main.h"
#include "Lista.h"
#define LINE_SIZE 256

void main()
{
	Lista* node = NULL;
	Lista* head = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char* token = NULL;
		char buffer[LINE_SIZE];
		char delimiter[] = ",";
		unsigned int id;
		char* pacient[LINE_SIZE];
		char* medic[LINE_SIZE];
		char* statut[LINE_SIZE];
		unsigned char nr_med;
		float compensare;

		int index = 0;
		int pozitii[] = { 4,2,3,1,0 };
		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			id = atoi(token);

			token = strtok(NULL, delimiter);
			strcpy(pacient, token);

			token = strtok(NULL, delimiter);
			strcpy(medic, token);

			token = strtok(NULL, delimiter);
			strcpy(statut, token);

			token = strtok(NULL, delimiter);
			nr_med = atoi(token);

			token = strtok(NULL, delimiter);
			compensare = atof(token);

			Reteta* reteta = createReteta(id, pacient, medic, statut, nr_med, compensare);
			//printReteta(reteta);
			node = insertTail(node, reteta);
			//insertHead(&head, reteta);
			//node = insertPoz(node, reteta, pozitii[index]);
			//index++;
			
		}
		display(node);
		printf("\n-------------------------\n");
		//display(head);
		deleteRetete(&node, 5);
		display(node);

	}
}

