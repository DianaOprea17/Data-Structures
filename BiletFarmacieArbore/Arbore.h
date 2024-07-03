#pragma once
#include "Farmacie.h"
#include "main.h"

typedef struct Arbore
{
	struct Arbore* left;
	struct Arbore* right;
	Farmacie* info;
}Arbore;

Arbore* createNode(Farmacie* info)
{
	Arbore* node = (Arbore*)malloc(sizeof(Arbore));
	node->info = info;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void upsert(Arbore** root, Farmacie* info)
{
	if (*root == NULL)
	{
		*root = createNode(info);
	}
	else {
		if ((*root)->info->id > info->id)
			upsert(&(*root)->left, info);
		else if ((*root)->info->id < info->id)
			upsert(&(*root)->right, info);
		else {
			(*root)->info = info;
		}
	}
}

//inordine: L - Rad - R

void inordine(Arbore* root)
{
	if (root)
	{
		inordine(root->left);
		printFarmacie(root->info);
		inordine(root->right);
	}
}

//nr total de angajati de la o anumita locatie

int nrAngajati(Arbore** root, const char* localitate) {
	int suma = 0;

	if (*root) {

		if (strcmp((*root)->info->localitate, localitate) == 0) 
			suma+= (*root)->info->nr_angajati + nrAngajati(&(*root)->left, localitate) + nrAngajati(&(*root)->right, localitate);
		else {
			nrAngajati(&(*root)->left, localitate);
			nrAngajati(&(*root)->right, localitate);
		}
	}
	
	return suma;
}

//cifra de afaceri medie lunara 

float cifraLunara(Arbore** root, unsigned short int id)
{
	float cf = 0;

	if (*root)
	{
		if ((*root)->info->id > id)
			cifraLunara(&(*root)->left, id);
		else if ((*root)->info->id < id)
			cifraLunara(&(*root)->right, id);
		else {
			return (*root)->info->cifra_afaceri / 12;
		}
	}

}

void deleteFullNode(Arbore** root, Arbore** rDesc)
{
	if ((*rDesc)->left)
	{
		deleteFullNode(*root, &(*rDesc)->left);
	}
	else {
		deleteFarmacie((*root)->info);
		(*root)->info = (*rDesc)->info;
		Arbore* tmp = *rDesc;
		*rDesc = (*rDesc)->right;
		free(tmp);
	}
}

int maxim(int a, int b)
{
	return a > b ? a : b;
}

int getHeight(Arbore* root)
{
	if (root)
		return 1 + maxim(getHeight(root->left), getHeight(root->right));
	else return 0;
}

void deleteFrunze(Arbore** root, int nivel)
{
	if (*root)
	{
		if (nivel == 1)
		{
			if ((*root)->left == NULL && (*root)->right == NULL)
			{
				deleteFarmacie((*root)->info);
				free(*root);
				*root = NULL;
			}
		}

		if (nivel > 1) {
			deleteFrunze(&(*root)->left, nivel - 1);
			deleteFrunze(&(*root)->right, nivel - 1);
		}

	}
}

void deleteFrunzeNivel(Arbore** root, int nivel)
{
	int inaltime = getHeight(*root);
	int deleteLevel = inaltime - nivel+1;

	deleteFrunze(root, deleteLevel);
}