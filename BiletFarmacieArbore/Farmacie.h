#pragma once
#include "main.h"

typedef struct Farmacie
{
	unsigned short int id;
	char* denumire;
	float cifra_afaceri;
	char* sef;
	unsigned char nr_angajati;
	char* localitate;

}Farmacie;

Farmacie* createFarmacie(unsigned short int id, char* den, float cf, char* sef, unsigned char ang, char* loc)
{
	Farmacie* node = (Farmacie*)malloc(sizeof(Farmacie));
	node->id = id;
	node->denumire = (char*)malloc(strlen(den) + 1);
	strcpy(node->denumire, den);
	node->cifra_afaceri = cf;
	node->sef = (char*)malloc(strlen(sef) + 1);
	strcpy(node->sef, sef);
	node->nr_angajati = ang;
	node->localitate = (char*)malloc(strlen(loc) + 1);
	strcpy(node->localitate, loc);
	return node;
}

void printFarmacie(Farmacie* f)
{
	printf("ID: %d, Denumire: %s, Cifra de afaceri: %.2f, Farmacist Sef: %s, Nr angajati: %d, Localitate: %s", f->id, f->denumire, f->cifra_afaceri, f->sef, f->nr_angajati, f->localitate);
}

void deleteFarmacie(Farmacie* f)
{
	if (f)
	{
		free(f->denumire);
		free(f->localitate);
		free(f->sef);
		free(f);
	}
}