#pragma once
#include "Raport.h"
#include "main.h"

typedef struct Lista
{
	struct Lista* next;
	struct Lista* prev;
	Raport* info;
}Lista;

Lista* createNode(Raport* info)
{
	Lista* node = (Lista*)malloc(sizeof(Lista));
	node->info = info;
	node->next = NULL;
	node->prev = NULL;
	return node;
}
void swap(Lista* a, Lista* b)
{
	Raport* aux = a->info;
	a->info = b->info;
	b->info = aux;
}


Lista* insertTail(Lista* head, Raport* info)
{
	Lista* result = head;
	Lista* node = createNode(info);

	if (head == NULL)
	{
		result = node;
	}
	else
	{
		while (head->next)
			head = head->next;
		node->prev = head;
		head->next = node;
	}

	
	return result;
}

void display(Lista* node)
{
	while (node)
	{
		printRaport(node->info);
		node = node->next;
	}
}



void sorteaza(Lista** node)
{
	Lista* tmp ;
	Lista* tmp2 ;
	int swapped;

	do
	{
		tmp = *node;
		swapped = 0;
		while (tmp->next)
		{
			if (tmp->info->cod > tmp->next->info->cod)
			{
				swap(tmp, tmp->next);
				swapped = 1;
			}


			tmp = tmp->next;
		}
		tmp2 = tmp;
	} while (swapped);
}

bool existaAbatere(Lista* node)
{
	while (node)
	{
		for (int i = 0; i < node->info->nr_analize; i++)
		{
			float abatere = ((node->info->val_ref[i] - node->info->val_def[i]) / node->info->val_ref[i]) * 100;
			if (abatere >= 50)
				return true;
			
		}
		node = node->next;
	}
	return false;
}

bool Eduplicat(Lista* node)
{
	for (Lista* curent = node; curent != NULL; curent = curent->next)
	{
		for (Lista* next = curent->next; next != NULL; next = next->next)
		{
			if (curent->info->id == next->info->id)
				return true;
		}
	}
	return false;
}

int nrUnic(Lista* node)
{
	int count = 0;
	while (node)
	{
		if (!Eduplicat(node))
			count++;
		node = node->next;
	}
	return count;
}