#pragma once
#include "main.h"
#include "Proiect.h"

typedef struct ListaD
{
	struct ListaD* next;
	struct ListaD* prev;
	Proiect* info;
}ListaD, * PListNode;

ListaD* createNode(Proiect* info)
{
	ListaD* node = (ListaD*)malloc(sizeof(ListaD));
	node->next = NULL;
	node->prev = NULL;
	node->info = info;
	return node;
}

ListaD* insertTail(ListaD* head, Proiect* info)
{
	ListaD* result = head;
	ListaD* node = createNode(info);
	if (result == NULL)
	{
		result = node;
	}
	else {
		while (head->next != NULL)
			head = head->next;
		node->prev = head;
		head->next = node;
	}
	return result;
}

void display(ListaD* node)
{
	while (node != NULL)
	{
		printProiect(node->info);
		
		node = node->next;
	}

}

int nrProiecte(ListaD* node, unsigned char exec)
{
	int count = 0;

	while (node)
	{
		if (node->info->nr_executanti > exec)
			count++;
		node = node->next;
	}

	return count;
}

void schimbaBuget(ListaD* node, const char* beneficiar, float procent)
{
	while (node)
	{
		if (strcmp(node->info->beneficiar, beneficiar) == 0)
			node->info->buget = node->info->buget + node->info->buget * procent / 100;
		node = node->next;
	}
}

void swap(ListaD* a, ListaD* b)
{
	Proiect* aux = a->info;
	a->info = b->info;
	b->info = aux;
}

void sortat(ListaD** node)
{
	ListaD* tmp;
	ListaD* altTmp = NULL;
	int swapped;
	do {
		swapped = 0;
		tmp = *node;
		while (tmp->next)
		{
			if (tmp->info->buget > tmp->next->info->buget)
			{
				swap(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
		altTmp = tmp;
	} while (swapped);
}

Proiect** salveazaVector(ListaD* head, int* size, const char* benef)
{
	int count = 0;
	ListaD* node = head;
	while (node)
	{
		if (strcmp(node->info->beneficiar, benef) == 0)
			count++;
		node = node->next;
	}

	int index = 0;
	Proiect** vector = (Proiect**)malloc(sizeof(Proiect*) * count);

	node = head;

	while (node)
	{
		if (strcmp(node->info->beneficiar, benef) == 0)
			vector[index++] = createProiect(node->info->cod, node->info->titlu, node->info->beneficiar, node->info->nr_executanti, node->info->buget);
		node = node->next;
	}

	*size = index;
	return vector;

}

void afisareVector(Proiect** vector, int size)
{
	for (int i = 0; i < size; i++)
	{
		printProiect(vector[i]);
	}
}