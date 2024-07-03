#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Consultatie.h"
#include "Graf.h"

#define LINE_SIZE 256
void main()
{
	Graf* graf= NULL;
	

	FILE* pFile = fopen("Data.txt", "r");

	if (pFile)
	{
		char* token = NULL;
		char buffer[LINE_SIZE];
		char delimiter[] = ",";
		char* data[LINE_SIZE];
		char* medic[LINE_SIZE];
		char* pacient[LINE_SIZE];
		char* specialitate[LINE_SIZE];
		char* diagnostic[LINE_SIZE];
		int pret;
		int index = 0;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(data, token);
			token = strtok(NULL, delimiter);
			strcpy(medic, token);
			token = strtok(NULL, delimiter);
			strcpy(pacient, token);
			token = strtok(NULL, delimiter);
			strcpy(specialitate, token);
			token = strtok(NULL, delimiter);
			strcpy(diagnostic, token);
			token = strtok(NULL, delimiter);
			pret = atoi(token);

			Consultatie* c = createCons(data, medic, pacient, specialitate, diagnostic, pret);
			//printConsultatie(c);
			addEdge(&graf, c);

		}
		displayGraf(graf);

		int suma = sumaCons(graf, "cardiologie");
		printf("\nsuma cons: %d \n", suma);

		modifPret(graf, "17/05", 1000);
		displayGraf(graf);

		stergere(&graf, "ventricul");
		displayGraf(graf);
	}
}