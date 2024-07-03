#pragma once
#include "main.h"
#include "Reteta.h"

typedef struct Lista
{
	struct Lista* next;
	struct Lista* prev;
	Reteta* info;
}Lista;

Lista* createNode(Reteta* info)
{
	Lista* node = (Lista*)malloc(sizeof(Lista));
	node->info = info;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

Lista* insertTail(Lista* head, Reteta* info)
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

		head->next = node;
		node->prev = head;
		
	}
	return result;
}

Lista* insertPoz(Lista* head, Reteta* info, int poz)
{
	Lista* result = head;
	Lista* node = createNode(info);
	
	if (head == NULL)
	{
		if (poz == 0)
			result = node;
		else
			result = NULL;
	}
	else
	{
		Lista* nodCurent = head;

		int pozitii = 0;
		while (nodCurent)
		{
			pozitii++;
			nodCurent = nodCurent->next;
		}

		//daca poz =0, inserare la inceput
		if (poz == 0)
		{
			node->next = head;
			head->prev = node;
			result = node;
		}
		else if (poz >= pozitii) //inserare la final
		{
			nodCurent = head;
			while (nodCurent->next != NULL) {
				nodCurent = nodCurent->next;
			}
			nodCurent->next = node;
			node->prev = nodCurent;
		}
		else { //inserare la mijloc
			nodCurent = head;
			for (int i = 0; i < poz; i++)
			{
				nodCurent = nodCurent->next;
			}
			node->next = nodCurent->next;
			if (nodCurent->next != NULL)
				nodCurent->next->prev = node;
			node->prev = nodCurent;
			nodCurent->next = node;
		}
	}

	return result;
}

void insertHead(Lista** head, Reteta* info)
{
	Lista* node = createNode(info);
	node->next = *head;
	*head = node;
}

void display(Lista* node)
{
	while (node)
	{
		printReteta(node->info);
		node = node->next;
	}
}

//sterge nodurile cu un nr de med mai mic decat un anumit nr

void deleteNode(Lista* node)
{
	if (node->prev)
	{
		node->prev->next = node->next;
	}
	if (node->next)
		node->next->prev = node->prev;

	deleteReteta(node->info);
	free(node);
}

void deleteRetete(Lista** head, int med)
{
	Lista* node = *head;
	while (node)
	{
		if (node->info->nr_med < med)
		{
			Lista* tmp = node;
			if (node == *head)
			{
				*head = (*head)->next;
				if (*head != NULL)
					(*head)->prev = NULL;
			}




			node = node->next;
			deleteNode(tmp);
		}
		else
			node = node->next;
	}
}
