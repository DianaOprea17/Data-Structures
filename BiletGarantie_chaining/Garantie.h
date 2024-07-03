#pragma once
#include "main.h"

typedef struct Garantie
{
	char* produs;
	unsigned int luni;
	unsigned char esteElectronic;
	char* service;
}Garantie;

Garantie* createGarantie(char* produs, unsigned int luni, unsigned char electr, char* service)
{
	Garantie* g = (Garantie*)malloc(sizeof(Garantie));
	g->produs = (char*)malloc(strlen(produs) + 1);
	strcpy(g->produs, produs);
	g->luni = luni;
	g->esteElectronic = electr;
	g->service = (char*)malloc(strlen(service) + 1);
	strcpy(g->service, service);
	return g;
}

void printGarantie(Garantie* g)
{
	if (g) {
		printf("Produs: %s, Luni: %d, E Electronic: %u, Service: %s\n", g->produs, g->luni, g->esteElectronic, g->service);
	}
}

void deleteGarantie(Garantie* g)
{
	if (g != NULL)
	{
		free(g->produs);
		free(g->service);
		free(g);
	}
}
