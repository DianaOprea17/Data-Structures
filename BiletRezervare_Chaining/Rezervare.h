#pragma once
#include "main.h"

typedef struct Rezervare
{
	unsigned int id;
	char* hotel;
	unsigned char categorie_hotel;
	char* client;
	unsigned char nr_zile;
	float suma;
}Rezervare;

Rezervare* createRezervare(unsigned int id, char* hotel, unsigned char categ, char* client, unsigned char zile, float suma)
{
	Rezervare* rez = (Rezervare*)malloc(sizeof(Rezervare));
	rez->id = id;
	rez->hotel = (char*)malloc(strlen(hotel) + 1);
	strcpy(rez->hotel, hotel);
	rez->categorie_hotel = categ;
	rez->client = (char*)malloc(strlen(client) + 1);
	strcpy(rez->client, client);
	rez->nr_zile = zile;
	rez->suma = suma;
	return rez;
}

void printRezervare(Rezervare* r)
{
	printf("ID: %d, Hotel: %s, Categorie: %u, Client: %s, Zile: %u, Plata: %.2f RON \n", r->id, r->hotel, r->categorie_hotel, r->client, r->nr_zile, r->suma);
}

void deleteRezervare(Rezervare* r)
{
	if (r)
	{
		free(r->hotel);
		free(r->client);
		free(r);

	}
}