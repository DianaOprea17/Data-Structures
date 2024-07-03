#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Farmacie.h"
#include "Arbore.h"
#define LINE_SIZE 256



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
		float cifra_afaceri;
		char* sef[LINE_SIZE];
		unsigned char nr_angajati;
		char* localitate[LINE_SIZE];

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			id = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(denumire, token);
			token = strtok(NULL, delimiter);
			cifra_afaceri = atof(token);
			token = strtok(NULL, delimiter);
			strcpy(sef, token);
	
			token = strtok(NULL, delimiter);
			nr_angajati = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(localitate, token);
	

			Farmacie* f = createFarmacie(id, denumire, cifra_afaceri, sef, nr_angajati, localitate);
			//printFarmacie(f);

			upsert(&root, f);
		}

		inordine(root);
		int suma = nrAngajati(&root, "Ploiesti");

		printf("\nNr Angajati: %d\n", suma);

		float cf = cifraLunara(&root, 2);
		printf("\nCifra: %.2f\n", cf);

		deleteFrunze(&root, 2);
		inordine(root);
	}
}