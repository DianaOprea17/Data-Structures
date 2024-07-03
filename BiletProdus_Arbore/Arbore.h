#pragma once
#include "main.h"
#include "Produs.h"

typedef struct Arbore
{
	struct Arbore* left;
	struct Arbore* right;
	Produs* info;
}Arbore;

Arbore* createNode(Produs* info)
{
	Arbore* node = (Arbore*)malloc(sizeof(Arbore));
	node->info = info;
	node->left = NULL;
	node->right = NULL;
}

void upsert(Arbore** root, Produs* info)
{
	if (*root == NULL)
	{
		*root = createNode(info);
	}
	else
	{
		if ((*root)->info->id > info->id)
			upsert(&(*root)->left, info);
		else if ((*root)->info->id < info->id)
			upsert(&(*root)->right, info);
		else
			(*root)->info = info;
	}
}

void inordine(Arbore* root)
{
	if (root)
	{
		inordine(root->left);
		printProdus(root->info);
		inordine(root->right);
	}
}

//nr de produse cu stoc mai mare decat un prag

int countProduse(Arbore** root, int prag)
{
	int count = 0;

	if (*root)
	{
		if ((*root)->info->stoc > prag)
			return 1 + countProduse(&(*root)->left, prag) + countProduse(&(*root)->right, prag);
		else {
			countProduse(&(*root)->left, prag);
			countProduse(&(*root)->right, prag);
		}
	}
	else return 0;
	
}

//valoarea stocului mediu la clienti pt 1 produs

float stocMediu(Arbore** root, int id)
{
	float medie = 0;
	int suma = 0;

	if (*root)
	{
		if ((*root)->info->id > id)
			stocMediu(&(*root)->left, id);
		else if ((*root)->info->id < id)
			stocMediu(&(*root)->right, id);
		else {
			for (int i = 0; i < (*root)->info->nr_clienti; i++)
			{
				suma += (*root)->info->stocuri_clienti[i];
			}
			medie = (float)suma / (*root)->info->nr_clienti;
		}
	}

	medie = (float)suma / (*root)->info->nr_clienti;
	return medie;
}

void deleteRadacina(Arbore** root, Arbore** rDesc)
{
	if ((*rDesc)->left)
		deleteRadacina(*root, &(*rDesc)->left);

	else {
		deleteProdus((*root)->info);
		(*root)->info = (*rDesc)->info;
		Arbore* tmp = *rDesc;
		*rDesc = (*rDesc)->right;
		free(tmp);
	}
}

typedef struct Lista
{
	Produs* info;
	struct Lista* next;
}Lista;

Lista* createNodeLista(Produs* info)
{
	Lista* node = (Lista*)malloc(sizeof(Lista));
	node->info = info;
	node->next = NULL;
	return node;
}

void inserareList(Lista** node, Produs* info)
{
	Lista* n = createNodeLista(info);

	n->next = *node;
	*node = n;
}

void createLista(Arbore* root, int id, Lista** list) {

	if (root->info->id > id) {
		createLista(root->left, id, list); 
	}
	else if (root->info->id < id) {
		createLista(root->right, id, list); 
	}
	else {
		inserareList(list, root->info); 
	}
}

void afisareLista(Lista* node)
{
	while (node)
	{
		printProdus(node->info);
		node = node->next;
	}
}