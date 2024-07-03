#pragma once
#include "main.h"
#include "Garantie.h"

typedef struct Node
{
	struct Node* next;
	Garantie* info;
}Node;

typedef struct Hash
{
	Node** buckets;
	int size;
}Hash;

Node* createNode(Garantie* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->next = NULL;
	node->info = info;
	return node;
}

#define HASH_SIZE 26

int fHash(const char* key)
{
	return key[0] % HASH_SIZE;
}

void putHT(Hash hash, Garantie* info)
{
	int index = fHash(info->service);
	Node* node = createNode(info);

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
			printGarantie(node->info);
			node = node->next;
		}
	}
}

//nr de garantii dintr-un service

int nrGarantii(Hash* hash, const char* service)
{

	int count = 0;
	for (int i = 0; i < hash->size; i++)
	{
		Node* node = hash->buckets[i];
		while (node)
		{
			if (strcmp(node->info->service, service) == 0)
				count++;
			node = node->next;
		}
	}
	return count;
}

//extinde garantia cu un nr de luni daca e electronic

void extindeGarantie(Hash* hash, int luni)
{
	for (int i = 0; i < hash->size; i++)
	{
		Node* node = hash->buckets[i];
		while (node)
		{
			if (node->info->esteElectronic)
				node->info->luni += luni;
			node = node->next;
		}
	}
}

//modifica service ul pentru un produs primit ca parametru, cheia de cautare e tot service 
void modificaService(Hash* hash, const char* produs, const char* newService) 
{
	for (int i = 0; i < hash->size; i++) {
		Node* node = hash->buckets[i];
		while (node) 
		{
			if (strcmp(node->info->produs, produs) == 0) 
			{
				free(node->info->service);
				node->info->service = (char*)malloc(strlen(newService));
				strcpy(node->info->service, newService);
			}
			node = node->next;
		}
	}
}
