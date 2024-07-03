#pragma once
#include "main.h"

typedef struct Cursa {
	unsigned int nr_cursa;
	char* data;
	unsigned char nr_vag;
	unsigned short int nr_bilete[2];
	float pret_bilete[2];
}Cursa;

Cursa* createCursa(unsigned int cursa, const char* data, unsigned char nr_vag, unsigned short int nr_bil[2], float pret[2])
{
	Cursa* node = (Cursa*)malloc(sizeof(Cursa));
	
	node->nr_cursa = cursa;
	node->data = (char*)malloc(strlen(data) + 1);
	strcpy(node->data, data);
	node->nr_vag = nr_vag;
	node->pret_bilete[0] = pret[0];
	node->pret_bilete[1] = pret[1];
	node->nr_bilete[0] = nr_bil[0];
	node->nr_bilete[1] = nr_bil[1];
	/*memcpy(node->nr_bilete, nr_bil, sizeof(node->nr_bilete));
	memcpy(node->pret_bilete, pret, sizeof(node->pret_bilete));*/
	return node;
}

void printCursa(Cursa* cursa)
{
	if (cursa != NULL)
	{
		printf("Nr: %d Data: %s, Nr. vagon: %u, Nr. bilete cls I: %u, Nr. bilete cls II: %u, Pret bilet cls I: %.2f, Pret bilet cls II: %.2f \n", cursa->nr_cursa, cursa->data, cursa->nr_vag, cursa->nr_bilete[0],
			cursa->nr_bilete[1], cursa->pret_bilete[0], cursa->pret_bilete[1]);
	}
}

void deleteCursa(Cursa* cursa)
{
	if (cursa != NULL)
	{
		free(cursa->data);
		free(cursa);
	}
}
