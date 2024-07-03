#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Raport.h"
#define LINE_SIZE 256
#include "Lista.h"

void main()
{
	Lista* node = NULL;

	FILE* pFile = fopen("Data.txt", "r");

	if (pFile)
	{
		char* token = NULL;
		char buffer[LINE_SIZE];
		char delimiter[] = ",";
		unsigned int id;
		unsigned int cod;
		unsigned char nr_analize;
		char** analize;
		float* val_ref;
		float* val_def;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			id = atoi(token);
			token = strtok(NULL, delimiter);
			cod = atoi(token);
			token = strtok(NULL, delimiter);
			nr_analize = atoi(token);
			
			analize = (char**)malloc(sizeof(char*) * nr_analize);
			for (int i = 0; i < nr_analize; i++)
			{
				token = strtok(NULL, delimiter);
				analize[i] = (char*)malloc(strlen(token) + 1);
				strcpy(analize[i], token);
			}

			val_ref = (float*)malloc(sizeof(float) * nr_analize);
			for (int i = 0; i < nr_analize; i++)
			{
				token = strtok(NULL, delimiter);
				val_ref[i] = atof(token);
			}
			val_def = (float*)malloc(sizeof(float) * nr_analize);
			for (int i = 0; i < nr_analize; i++)
			{
				token = strtok(NULL, delimiter);
				val_def[i] = atof(token);
			}

			Raport* r = createRaport(id, cod, nr_analize, analize, val_ref, val_def);
			//printRaport(r);
			node = insertTail(node, r);
			
		}

		display(node);
		//sorteaza(&node);
		printf("\n");
		//display(node);

		bool abatere = existaAbatere(node);
		if (abatere)
		{
			printf("exista abatere");
		}
		else printf("Nu exista abatere");

		printf("\n\n");

		bool duplicat = Eduplicat(node);
		if (duplicat)
		{
			printf("exista duplicat");
		}else printf("nu exista duplicat");

		int count = nrUnic(node);
		printf("\nnr unice: %d", count);
	}
}