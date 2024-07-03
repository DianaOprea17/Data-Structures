#pragma once
#include "Consultatie.h"
#include "main.h"

typedef struct Graf;

typedef struct ListaAdiacenta
{
	Consultatie* info;
	struct ListaAdiacenta* nextNeighbour;
}Lista;

typedef struct Graf
{
	char* specialitate;
	struct Graf* next;
	Lista* vecini;
}Graf;

Graf* createNode(const char* specialitate)
{
	Graf* node = (Graf*)malloc(sizeof(Graf));
	node->specialitate = (char*)malloc(strlen(specialitate) + 1);
	strcpy(node->specialitate, specialitate);
	node->next = NULL;
	node->vecini = NULL;
	return node;
}

Graf* searchSpec(Graf* graf, const char* specialitate)
{
	while (graf != NULL && strcmp(graf->specialitate, specialitate) != 0)
		graf = graf->next;
	return graf;
}

void addNeighbour(Graf* graf, Consultatie* info)
{
	Lista* list = (Lista*)malloc(sizeof(Lista));
	list->info = info;
	list->nextNeighbour = graf->vecini;
	graf->vecini = list;
}

void addEdge(Graf** g, Consultatie* info)
{
	Graf* node = searchSpec(*g, info->specialitate);
	if (node == NULL)
	{
		node = createNode(info->specialitate);
		node->next = *g;
		*g = node;
	}

	addNeighbour(node, info);

}

void displayGraf(Graf* node)
{
	while (node)
	{
		printf("Specialitate: %s", node->specialitate);
		printf("\n");
		Lista* list = node->vecini;
		while (list)
		{
			
			
				printConsultatie(list->info);
				list = list->nextNeighbour;
			
			
		}
		printf("\n-----------------\n");
		node = node->next;
	}
}


//valoarea cons de la o anumita specialitate

int sumaCons(Graf* node, const char* specialitate)
{
	int suma = 0;
	while (node)
	{
		Lista* list = node->vecini;
		while (list)
		{
			if (strcmp(node->specialitate, specialitate) == 0)
				suma += list->info->pret;
			list = list->nextNeighbour;
		}
		node = node->next;
	}
	return suma;
}

//modifica pretul unei consultatii, specificata prin data

void modifPret(Graf* node, const char* data, int pretNou)
{
	while (node)
	{
		Lista* list = node->vecini;
		while (list)
		{
			if (strcmp(list->info->data, data) == 0)
				list->info->pret = pretNou;
			list = list->nextNeighbour;
		}
		node = node->next;
	}
}

void stergere(Graf** graf, const char* diagnostic)
{
	Graf* node = *graf;

	while (node)
	{
		Lista** list = &(node->vecini);
		while (*list)
		{
			if (strcmp((*list)->info->diagnostic, diagnostic) == 0)
			{
				Lista* tmp = *list;
				*list = (*list)->nextNeighbour;

				deleteCons(tmp->info);
			}
			list = &((*list)->nextNeighbour);
		}
		node = node->next;
	}
}