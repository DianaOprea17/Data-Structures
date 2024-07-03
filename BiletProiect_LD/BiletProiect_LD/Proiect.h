#pragma once
#include "main.h"

typedef struct Proiect
{
	unsigned int cod;
	char* titlu;
	char* beneficiar;
	unsigned char nr_executanti;
	float buget;
}Proiect;

Proiect* createProiect(unsigned int cod, const char* titlu, const char* benef, unsigned char nr_exec, float buget)
{
	Proiect* node = (Proiect*)malloc(sizeof(Proiect));
	node->cod = cod;
	node->titlu = (char*)malloc(strlen(titlu) + 1);
	node->beneficiar = (char*)malloc(strlen(benef) + 1);
	
	strcpy(node->titlu, titlu);
	strcpy(node->beneficiar, benef);

	node->nr_executanti = nr_exec;
	node->buget = buget;
	return node;
}

void printProiect(Proiect* node)
{
	if (node != NULL)
		printf("Cod: %d, Titlu: %s, Beneficiar: %s, Nr_executanti: %u, Buget: %.2f \n", node->cod, node->titlu, node->beneficiar, node->nr_executanti, node->buget);
}

void deleteProiect(Proiect* node)
{
	if (node != NULL)
	{
		free(node->beneficiar);
		free(node->titlu);
		free(node);
	}
}

