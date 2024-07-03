#pragma once
#include "Cursa.h"
#include "main.h"

typedef struct Arbore {
	struct Arbore* left;
	struct Arbore* right;
	Cursa* info;
}Arbore;

Arbore* createNode(Cursa* info)
{
	Arbore* node = (Arbore*)malloc(sizeof(Arbore));
	node->info = info;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void upsert(Arbore** root, Cursa* info)
{
	if (*root)
	{
		if ((*root)->info->nr_cursa > info->nr_cursa)
			upsert(&(*root)->left, info);
		else if ((*root)->info->nr_cursa < info->nr_cursa)
			upsert(&(*root)->right, info);
		else {
			(*root)->info = info;
		}
	}
	else *root = createNode(info);
}

void inordine(Arbore* root)
{
	if (root)
	{
		inordine(root->left);
		printCursa(root->info);
		inordine(root->right);
	}
}

//nr bilete cumparate la cls a 2a

int nrBilete(Arbore* root)
{
	int count = 0;
	if (root)
	{
		count += root->info->nr_bilete[1] + nrBilete(root->left)+ nrBilete(root->right);
		
		
	}
	return count;
}

//modif pretul bil de la cls 1

void changePret(Arbore* root, const char* data, float procent)
{
	if (root)
	{
		if (strcmp(root->info->data, data) == 0)
		{
			root->info->pret_bilete[0] += (root->info->pret_bilete[0] * procent) / 100;
		}
		else {
			changePret(root->left, data, procent);
			changePret(root->right, data, procent);
		}

	}
}

//cursa cu incasari maxime
//int maxim(int a, int b)
//{
//	return a > b ? a : b;
//}

float incasari(Arbore* root)
{
	float incasare = 0;
	if (root)
	{
		incasare = root->info->nr_bilete[0] * root->info->pret_bilete[0] + root->info->nr_bilete[1] * root->info->pret_bilete[1];

	}


	return incasare;
}

Arbore* cursaMax(Arbore* root)
{
	
	
	if (root == NULL)
		return NULL;

	Arbore* node = root;
	float maxim = incasari(root);
		
	Arbore* left = cursaMax(root->left);
	if (left) {
		float valL = incasari(left);
		if (maxim < valL)
		{
			maxim = valL;
			
			node = left;
		}
	}

	Arbore* right = cursaMax(root->right);
	if (right)
	{
		float valR = incasari(right);
		if (maxim < valR)
		{
			maxim = valR;
			
			node = root->right;
		}
	}

	return node;
}