#pragma once
#include "main.h"

typedef struct Produs
{
	unsigned short int id;
	char* denumire;
	unsigned short int stoc;
	unsigned char nr_clienti;
	unsigned short int* stocuri_clienti;
}Produs;

Produs* createProdus(unsigned short int id, char* den, unsigned short int stoc, unsigned char clienti, unsigned short int* stocuri)
{
	Produs* p = (Produs*)malloc(sizeof(Produs));
	p->id = id;
	p->denumire = (char*)malloc(strlen(den) + 1);
	strcpy(p->denumire, den);
	p->stoc = stoc;
	p->nr_clienti = clienti;
	p->stocuri_clienti = (unsigned short int*)malloc(sizeof(unsigned short int) * clienti);
	for (int i = 0; i < clienti; i++)
	{
		p->stocuri_clienti[i] = stocuri[i];
	}
	return p;
}

void printProdus(Produs* p)
{
	printf("ID: %d, Denumire: %s, Stoc: %u, NR Clienti:%u, Stocuri clienti: ", p->id, p->denumire, p->stoc, p->nr_clienti);
	for (int i = 0; i < p->nr_clienti; i++)
	{
		printf("%u", p->stocuri_clienti[i]);
		if (i < p->nr_clienti - 1)
			printf(", ");
	}
	printf("\n");
}

void deleteProdus(Produs* p)
{
	if (p)
	{
		free(p->denumire);
		free(p->stocuri_clienti);
		free(p);
	}
}