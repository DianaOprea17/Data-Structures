#pragma once
#include "main.h"

typedef struct Consultatie
{
	char* data;
	char* medic;
	char* pacient;
	char* specialitate;
	char* diagnostic;
	int pret;
}Consultatie;

Consultatie* createCons(char* data, char* medic, char* pacient, char* spec, char* diag, int pret)
{
	Consultatie* node = (Consultatie*)malloc(sizeof(Consultatie));
	node->data = (char*)malloc(strlen(data) + 1);
	strcpy(node->data, data);
	node->medic = (char*)malloc(strlen(medic) + 1);
	strcpy(node->medic, medic);
	node->pacient= (char*)malloc(strlen(pacient) + 1);
	strcpy(node->pacient, pacient);
	node->specialitate = (char*)malloc(strlen(spec) + 1);
	strcpy(node->specialitate, spec);
	node->diagnostic = (char*)malloc(strlen(diag) + 1);
	strcpy(node->diagnostic, diag);
	node->pret = pret;
	return node;
}

void printConsultatie(Consultatie* c)
{
	printf("Data: %s, Medic: %s, Pacient: %s, Specialitate: %s, Diagnostic: %s, Pret:%d \n", c->data, c->medic, c->pacient, c->specialitate, c->diagnostic, c->pret);
}

void deleteCons(Consultatie* c)
{
	if (c)
	{
		free(c->data);
		free(c->medic);
		free(c->pacient);
		free(c->specialitate);
		free(c->diagnostic);
		free(c);
	}
}