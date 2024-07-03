#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Cursa.h"
#include "Arbore.h"
#define LINE_SIZE 256

void main()
{

	Arbore* root = NULL;

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char* token = NULL;
		const char delimiter[] = ",";
		unsigned int nr_cursa;
		unsigned char nr_vag;
		unsigned short int nr_bilete[2];
		float pret_bilete[2];
		char buffer[LINE_SIZE];
		char data[LINE_SIZE];
		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);

			nr_cursa = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(data, token);

			token = strtok(NULL, delimiter);
			nr_vag = atoi(token);

			token = strtok(NULL, delimiter);
			nr_bilete[0] = (unsigned short int)atoi(token);

			token = strtok(NULL, delimiter);
			nr_bilete[1] = (unsigned short int)atoi(token);

			token = strtok(NULL, delimiter);
			pret_bilete[0] = atof(token);

			token = strtok(NULL, delimiter);
			pret_bilete[1] = atof(token);

			Cursa* cursa = createCursa(nr_cursa, data, nr_vag, nr_bilete, pret_bilete);
			//printCursa(cursa);
			upsert(&root, cursa);

		}

		inordine(root);

		int nr = nrBilete(root);
		printf("\nBilete cls a 2a: %d\n", nr);

		changePret(root, "17/07", 12);
		inordine(root);

		printf("\n MAXIM: \n");
		Arbore* node = cursaMax(root);
		printCursa(node->info);
	}
}