#pragma once
#include "main.h"
#include "Proiect.h"

typedef struct Hash
{
	Proiect** items;
	int size;
}Hash;

int fHash(const char* key, int size)
{
	int index = 0;
	for (int i = 0; i < strlen(key); i++)
	{
		index += key[i] *(strlen(key) - i);
	}
	return index % size;
}

#define HASH_SIZE 3

void putHT(Hash*, Proiect*);

void resizeHT(Hash* hash)
{
	Proiect** aux = hash->items;
	hash->items = (Proiect**)malloc(sizeof(Proiect*) * hash->size * 2);
	memset(hash->items, 0, sizeof(Proiect*) * hash->size * 2);
	hash->size *= 2;

	for (int i = 0; i < hash->size / 2; i++)
	{
		Proiect* node = aux[i];
		if (node)
		{
			putHT(hash, node);
		}
	}
}

int linearProbing(Hash* hash, const char* key, int index)
{
	while (hash->items[index] != NULL)
	{
		index++;
		if (index == hash->size)
		{
			resizeHT(hash);
			index = fHash(key, hash->size);
		}
	}

	return index;
}

void putHT(Hash* hash, Proiect* info)
{
	if (hash->items == NULL)
	{
		hash->items = (Proiect**)malloc(sizeof(Proiect*) * HASH_SIZE);
		memset(hash->items, 0, sizeof(Proiect*) * HASH_SIZE);
		hash->size = HASH_SIZE;
	}

	int index = fHash(info->beneficiar, hash->size);
	if (hash->items[index] != NULL)
	{
		index = linearProbing(hash, info->beneficiar, index);
	}

	hash->items[index] = info;
}

void display(Hash* hash)
{
	for (int i = 0; i < hash->size; i++)
	{
		printProiect(hash->items[i]);
	}
}

//bugetul unui beneficiar

float sumaBuget(Hash* hash, const char* beneficiar)
{
	float suma = 0;
	for (int i = 0; i < hash->size; i++)
	{
		Proiect* node = hash->items[i];
		if (node!=NULL && strcmp(node->beneficiar, beneficiar) == 0)
		{
			suma += node->buget;
		}
	}
	return suma;
}

//modif denumire benef

void modifBenef(Hash* hash, const char* benefVechi, const char* benefNou)
{
	int index = fHash(benefVechi, hash->size);
	for (int i = 0; i < hash->size; i++)
	{
		Proiect* node = hash->items[i];
		if (node != NULL && strcmp(node->beneficiar, benefVechi) == 0)
		{
			free(node->beneficiar);
			node->beneficiar = (char*)malloc(strlen(benefNou) + 1);
			strcpy(node->beneficiar, benefNou);
		}
	}
}

