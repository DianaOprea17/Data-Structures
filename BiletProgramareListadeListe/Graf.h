#pragma once
#include "main.h"
#include "Programare.h"

typedef struct ListaAdiacenta
{
	Programare* info;
	struct ListaAdiacenta* nextNeighbour;
}Lista;

typedef struct Graf
{
	char* data;
	struct Graf* next;
	Lista* vecini;
}Graf;

Graf* createNode(char* data)
{
	Graf* g = (Graf*)malloc(sizeof(Graf));
	g->data = (char*)malloc(strlen(data) + 1);
	strcpy(g->data, data);
	g->next = NULL;
	g->vecini = NULL;
	return g;
}

Graf* searchData(Graf* node, char* data)
{
	while (node != NULL && strcmp(node->data, data) != 0)
		node = node->next;
	return node;
}

void addVecin(Graf* node, Programare* info)
{
	Lista* list = (Lista*)malloc(sizeof(Lista));
	list->info = info;
	list->nextNeighbour = node->vecini;
	node->vecini = list;
}

void addEdge(Graf** g, Programare* info)
{
	Graf* node = searchData(*g, info->data_prog);

	if (node == NULL)
	{
		node = createNode(info->data_prog);
		node->next = *g;
		*g = node;
	}

	addVecin(node, info);
}

void display(Graf* node)
{
	while (node)
	{
		printf("Data: %s\n", node->data);

		Lista* list = node->vecini;

		while (list)
		{
			printProgramare(list->info);
			list = list->nextNeighbour;
		}

		printf("\n--------------------------\n");
		node = node->next;
	}
}

//valoarea programarilor la o anumita data

int valProg(Graf* node, char* data)
{
	int suma = 0;
	while (node)
	{
		Lista* list = node->vecini;

		while (list)
		{
			if (strcmp(list->info->data_prog, data) == 0)
				suma += list->info->pret;
			list = list->nextNeighbour;
		}
		node = node->next;
	}
	return suma;
}


void changeCost(Graf* node, char* client, int pretNou)
{
	while (node)
	{
		Lista* list = node->vecini;

		while (list)
		{
			if (strcmp(list->info->client, client) == 0)
			{
				list->info->pret = pretNou;
			}
			list = list->nextNeighbour;
		}
		node = node->next;
	}
}

//sterge programarile ale caror durate sunt mai mici decat un nr dat

void stergere(Graf** g, float durata)
{
	Graf* node = *g;

	while (node!=NULL)
	{
		Lista** list = &(node->vecini);
		while (*list !=NULL)
		{
			if ((*list)->info->durata < durata)
			{
				Lista* tmp = *list;
				*list = (*list)->nextNeighbour;
				deleteProg(tmp->info);
				free(tmp);
				continue;
			}
			

			list = &((*list)->nextNeighbour);
		}
		node = node->next;
	}
}

//parcurgere in adancime

typedef struct Stiva
{
	Programare* info;
	struct Stiva* next;
}Stiva;

Stiva* createNodeStiva(Programare* info)
{
	Stiva* node = (Stiva*)malloc(sizeof(Stiva));
	node->info = info;
	node->next = NULL;
	return node;
}

void push(Stiva** topstack, Programare* info)
{
	Stiva* node = createNodeStiva(info);
	node->next = *topstack;
	*topstack = node;
}

Programare* popNode(Stiva** topstack, Programare* info)
{
	Programare* result = NULL;

	if (*topstack)
	{
		result = (*topstack)->info;

		Stiva* tmp = *topstack;
		*topstack = tmp->next;
		free(tmp);

	}

	return result;
}

//sa se treaca in stiva programarile de un anumite serviciu

Stiva* addStiva(Graf* node, const char* serv)
{
	Stiva* result=NULL;
	while (node)
	{
		Lista* list = node->vecini;
		while (list)
		{
			if (strcmp(list->info->servicii, serv) == 0)
			{
				Programare* copy = list->info;
				push(&result, copy);
			}
			list = list->nextNeighbour;
		}
		node = node->next;
	}

	return result;
}

void printStiva(Stiva* stack)
{
	while (stack)
	{
		printProgramare(stack->info);
		stack = stack->next;
	}
}

//coada

typedef struct Coada
{
	Programare* info;
	struct Coada* next;
}Coada;

Coada* createNodeCoada(Programare* info)
{
	Coada* node = (Coada*)malloc(sizeof(Coada));
	node->info = info;
	node->next = NULL;
	return node;
}

void putCoada(Coada** coada, Programare* info)
{
	Coada* node = createNodeCoada(info);
	if (*coada == NULL)
	{
		node->next = node;
	}
	else {
		node->next = (*coada)->next;
		(*coada)->next = node;
	}
	*coada = node;
}

Coada* addCoada(Graf* node, const char* servicii)
{
	Coada* coada = NULL;
	while (node)
	{
		Lista* list = node->vecini;
		while (list)
		{
			if (strcmp(list->info->servicii, servicii) == 0)
			{
				Programare* copy = list->info;
				putCoada(&coada, copy);
			}
			list = list->nextNeighbour;
		}

		node = node->next;
	}
	return coada;
}

void printCoada(Coada* coada)
{
	Coada* node = coada->next;
	do
	{
		printProgramare(node->info);
		node = node->next;
	} while (node != coada->next);
}