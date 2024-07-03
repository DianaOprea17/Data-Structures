#pragma once
#include "main.h"
#include "Rezervare.h"

typedef struct Node
{
	struct Node* next;
	Rezervare* info;
}Node;

typedef struct Hash
{
	Node** buckets;
	int size;
}Hash;

Node* createNode(Rezervare* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->next = NULL;
	node->info = info;
	return node;
}

#define HASH_SIZE 26

int fHash(unsigned char key)
{
	return key % HASH_SIZE;
}

void putHT(Hash hash, Rezervare* rez)
{
	int index = fHash(rez->categorie_hotel);
	Node* node = createNode(rez);

	node->next = hash.buckets[index];
	hash.buckets[index] = node;
}

void display(Hash* hash)
{
	for (int i = 0; i < hash->size; i++)
	{
		Node* node = hash->buckets[i];
		while (node)
		{
			printRezervare(node->info);
			node = node->next;
		}
	}
}

//nr de rezervari pt o categorie de hotel

int nrRez(Hash hash, unsigned char categ)
{
	int count = 0;

	for (int i = 0; i < hash.size; i++)
	{
		Node* node = hash.buckets[i];

		while (node)
		{
			if (node->info->categorie_hotel == categ)
				count++;
			node = node->next;
		}
	}

	return count;
}

//modifica categoria pentru un hotel dat prin denumire

void changeCateg(Hash hash, const char* hotel, unsigned char categ)
{

	for (int i = 0; i < hash.size; i++)
	{
		Node* node = hash.buckets[i];

		while (node)
		{
			if (strcmp(node->info->hotel, hotel) == 0)
			{
				node->info->categorie_hotel = categ;
			}
			node = node->next;
		}
	}
}

//schimba numele unui hotel cu alt hotel care l-a cumparat

void changeName(Hash hash, const char* hotel, const char* hotelMama)
{
	for (int i = 0; i < hash.size; i++)
	{
		Node* node = hash.buckets[i];
		while (node)
		{
			if (strcmp(node->info->hotel, hotel) == 0)
			{
				free(node->info->hotel);
				node->info->hotel = (char*)malloc(strlen(hotelMama) + 1);
				strcpy(node->info->hotel, hotelMama);

			}
			node = node->next;
		}
	}
}

typedef struct LinearProbing
{
	Rezervare** items;
	int size;
}LinearProbing;

int fHashNou(const char* client, int size)
{
	int index = 0;

	for (int i = 0; i < strlen(client); i++)
	{
		index += (strlen(client) - i) * client[i];
	}
	return index % size;
}

void putLP(LinearProbing*, Rezervare*);

void resizeHT(LinearProbing* hash)
{
	Rezervare** aux = hash->items;
	hash->items = (Rezervare**)malloc(sizeof(Rezervare*) * hash->size * 2);
	memset(hash->items, 0, sizeof(Rezervare*) * hash->size * 2);
	hash->size *= 2;
	for (int i = 0; i < hash->size / 2; i++)
	{
		Rezervare* node = aux[i];
		if (node)
			putLP(hash, node);
	}
}

int linearP(LinearProbing* hash, const char* key, int index)
{
	if (hash->items[index] != NULL)
	{
		index++;
		if (index == hash->size)
		{
			resizeHT(hash);
			index = fHashNou(key, hash->size);
		}
	}
	return index;
}

void putLP(LinearProbing* hash, Rezervare* info)
{
	if (hash->items == NULL)
	{
		hash->items = (LinearProbing*)malloc(sizeof(LinearProbing) * HASH_SIZE);
		memset(hash->items, 0, sizeof(LinearProbing) * HASH_SIZE);
		hash->size = HASH_SIZE;
	}

	int index = fHashNou(info->client, hash->size);

	if (hash->items[index]!=NULL)
	{
		index = linearP(hash, info->client, index);
	}

	hash->items[index] = info;

}

void creeazaLP(Hash hash, LinearProbing* lp, unsigned char categ)
{
	
	for (int i = 0; i < hash.size; i++)
	{
		Node* node = hash.buckets[i];
		while (node)
		{

			if (node->info->categorie_hotel == categ)
			{
				lp = (LinearProbing*)malloc(sizeof(LinearProbing));
				putLP(lp, node->info);
			}
			node = node->next;
		}
	}
}

void displayLP(LinearProbing* hash)
{
	for (int i = 0; i < hash->size; i++)
	{
		printRezervare(hash->items[i]);
	}
}