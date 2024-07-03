#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Rezervare.h"
#include "Hash.h"
#define LINE_SIZE 256

void main()
{
	Hash hash = { .buckets = NULL, .size = HASH_SIZE };
	hash.buckets = (Node**)malloc(sizeof(Node*) * HASH_SIZE);
	memset(hash.buckets, 0, sizeof(Node*) * HASH_SIZE);

	FILE* pFile = fopen("Data.txt", "r");

	if (pFile)
	{
		char* token = NULL;
		char buffer[LINE_SIZE];
		char delimiter[] = ",";
		unsigned int id;
		char* hotel[LINE_SIZE];
		unsigned char categorie_hotel;
		char* client[LINE_SIZE];
		unsigned char nr_zile;
		float suma;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			id = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(hotel, token);
			token = strtok(NULL, delimiter);
			categorie_hotel = (unsigned char)atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(client, token);
			token = strtok(NULL, delimiter);
			nr_zile = (unsigned char)atoi(token);
			token = strtok(NULL, delimiter);
			suma = atof(token);

			Rezervare* rez = createRezervare(id, hotel, categorie_hotel, client, nr_zile, suma);
			//printRezervare(rez);

			putHT(hash, rez);
		}

		display(&hash);

		int count = nrRez(hash, 5);
		printf("\nNr rez: %d \n", count);

		changeCateg(hash, "Hotel Varna", 4);
		display(&hash);

		printf("\n----------\n");

		changeName(hash, "Hotel Central", "Hotel International");
		display(&hash);

		LinearProbing lp = { .items = NULL, .size = 0 };
		creeazaLP(hash, &lp, 5);

		printf("\n");

		
	}
}