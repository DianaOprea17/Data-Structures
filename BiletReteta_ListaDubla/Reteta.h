#pragma once
#include "main.h"

typedef struct Reteta
{
	unsigned int id;
	char* pacient;
	char* medic;
	char* statut;
	unsigned char nr_med;
	float compensare;

}Reteta;

Reteta* createReteta(unsigned int id, char* pacient, char* medic, char* statut, unsigned char nr_med, float compens)
{
	Reteta* rez = (Reteta*)malloc(sizeof(Reteta));
	rez->id = id;
	rez->pacient = (char*)malloc(strlen(pacient) + 1);
	strcpy(rez->pacient, pacient);

	rez->medic = (char*)malloc(strlen(medic) + 1);
	strcpy(rez->medic, medic);

	rez->statut = (char*)malloc(strlen(statut) + 1);
	strcpy(rez->statut, statut);

	rez->nr_med = nr_med;
	rez->compensare = compens;
	return rez;
}

void printReteta(Reteta* rez)
{
	printf("ID: %d, Pacient: %s, Medic: %s, Statut: %s, Nr medicamente: %u, Compensare: %.2f \n", rez->id, rez->pacient, rez->medic, rez->statut, rez->nr_med, rez->compensare);
}

void deleteReteta(Reteta* rez)
{
	if (rez)
	{
		free(rez->medic);
		free(rez->pacient);
		free(rez->statut);
		free(rez);
	}
}
