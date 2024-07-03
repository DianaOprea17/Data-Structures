#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#include "main.h"
#include "Garantie.h"
#include "Chain.h"

void main()
{
	Hash hash = {
		.buckets = NULL,
		.size = HASH_SIZE
	};
	hash.buckets = (Node**)malloc(sizeof(Node*) * HASH_SIZE);
	memset(hash.buckets, 0, sizeof(Node*) * HASH_SIZE);

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char* token;
		char delimiter[] = ",";
		char buffer[LINE_SIZE];
		char* produs[LINE_SIZE];
		unsigned int luni;
		unsigned char esteElectronic;
		char* service[LINE_SIZE];
		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(produs, token);
			token = strtok(NULL, delimiter);
			luni = atoi(token);
			token = strtok(NULL, delimiter);
			esteElectronic = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(service, token);
			Garantie* g = createGarantie(produs, luni, esteElectronic, service);
			//printGarantie(g);
			putHT(hash, g);
		}
		display(&hash);
		
		printf("\n--------------------------\n");
		int count = nrGarantii(&hash, "ServiceTrei");
		printf("Garantii: %d \n", count);

		extindeGarantie(&hash, 12);
		display(&hash);

		printf("\n--------------------------\n");
		modificaService(&hash, "Produs3", "Dristor");
		display(&hash);

	}
}