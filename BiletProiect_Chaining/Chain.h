#pragma once
#include "main.h"
#include "Proiect.h"
#define HASH_SIZE 26

typedef struct Node
{
	Proiect* info;
	struct Node* next;
}Node;

typedef struct Hash
{
	Node** buckets;
	int size;
}Hash;

Node* createNode(Proiect* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->next = NULL;
	return node;
}

int fHash(const char* key)
{
	return key[0] % HASH_SIZE;
}

void putHT(Hash hash, Proiect* info)
{
	int index = fHash(info->beneficiar);
	Node* node = createNode(info);
	node->next = hash.buckets[index];
	hash.buckets[index] = node;
}

void display(Hash* hash)
{
	for (int i = 0; i < hash->size; i++)
	{
		Node* node = hash->buckets[i];
		while(node)
		{
			printProiect(node->info);
			node = node->next;
		}
	}
}

//bugetul total al unui beneficiar

float bugetTotal(Hash* hash, const char* beneficiar)
{
	float suma = 0;

	for (int i = 0; i < hash->size; i++)
	{
		Node* node = hash->buckets[i];
		while (node)
		{
			if (strcmp(node->info->beneficiar, beneficiar) == 0)
				suma += node->info->buget;
			node = node->next;
		}
	}

	return suma;
}

//schimba nume beneficiar

void changeName(Hash* hash, const char* numeVechi, const char* numeNou)
{
	for (int i = 0; i < hash->size; i++)
	{
		Node* node = hash->buckets[i];
		while (node)
		{
			if (strcmp(node->info->beneficiar, numeVechi) == 0)
			{
				free(node->info->beneficiar);
				node->info->beneficiar = (char*)malloc(strlen(numeNou) + 1);
				strcpy(node->info->beneficiar, numeNou);
			}
			node = node->next;
		}
	}
}

//sterge pt benef

void sterge(Hash* hash, const char * benef)
{
	for (int i = 0; i < hash->size; i++)
	{
		Node* node = hash->buckets[i];
		Node* prev = NULL;
		while (node)
		{
			if (strcmp(node->info->beneficiar, benef) == 0)
			{
				Node* tmp = node;
				if (prev)
					prev->next = node->next;
				else hash->buckets[i] = node->next;
				node = node->next;
				deleteProiect(tmp->info);
				free(tmp);
			}
			else
			{
				prev = node;
				node = node->next;
			}
		}
	}
}