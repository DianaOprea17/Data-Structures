#pragma once
#include "main.h"

typedef struct Programare
{
	char* data_prog;
	char* client;
	float durata;
	char* servicii;
	int pret;
}Programare;

Programare* createProgramare(char* data, char* client, float durata, char* servicii, int pret)
{
	Programare* node = (Programare*)malloc(sizeof(Programare));
	node->data_prog = (char*)malloc(strlen(data) + 1);
	strcpy(node->data_prog, data);
	node->client = (char*)malloc(strlen(client) + 1);
	strcpy(node->client, client);
	node->durata = durata;
	node->servicii = (char*)malloc(strlen(servicii) + 1);
	strcpy(node->servicii, servicii);
	node->pret = pret;
	return node;
}

void printProgramare(Programare* p)
{
	printf("Data: %s, Client: %s, Durata: %.2f, Servicii: %s, Pret: %d \n", p->data_prog, p->client, p->durata, p->servicii, p->pret);
}

void deleteProg(Programare* p)
{
	if (p)
	{
		free(p->data_prog);
		free(p->client);
		free(p->servicii);
		free(p);
	}
}