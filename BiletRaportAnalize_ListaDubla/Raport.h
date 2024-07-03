#pragma once
#include "main.h"

typedef struct Raport
{
	unsigned int id;
	unsigned int cod;
	unsigned char nr_analize;
	char** analize;
	float* val_ref;
	float* val_def;

}Raport;

Raport* createRaport(unsigned int id, unsigned int cod, unsigned char nr, char** analize, float* ref, float* det)
{
	Raport* r = (Raport*)malloc(sizeof(Raport));

	r->id = id;
	r->cod = cod;
	r->nr_analize = nr;
	r->analize = (char**)malloc(sizeof(char*) * nr);
	for (int i = 0; i < nr; i++)
	{
		r->analize[i] = (char*)malloc(strlen(analize[i]) + 1);
		strcpy(r->analize[i], analize[i]);
	}

	r->val_ref = (float*)malloc(sizeof(float)*nr);
	for (int i = 0; i < nr; i++)
	{
		r->val_ref[i] = ref[i];
	}

	r->val_def = (float*)malloc(sizeof(float) * nr);

	for (int i = 0; i < nr; i++)
	{
		r->val_def[i] = det[i];
	}

	return r;
}

void printRaport(Raport* r)
{
	printf("ID: %d, Cod pacient: %d, Nr analize: %u, Analize: ", r->id, r->cod, r->nr_analize);
	for (int i = 0; i < r->nr_analize; i++)
	{
		printf("%s, ", r->analize[i]);
		
	}
	printf("Valoare de referinta: ");
	for (int i = 0; i < r->nr_analize; i++)
	{
		printf("%.2f, ", r->val_ref[i]);

	}
	printf("Valoare determinata: ");
	for (int i = 0; i < r->nr_analize; i++)
	{
		printf("%.2f ", r->val_def[i]);
		if (i < r->nr_analize - 1)
			printf(", ");

	}
	printf("\n");
}

void deleteRaport(Raport* r)
{
	if (r)
	{
		free(r->val_def);
		free(r->val_ref);
		for (int i = 0; i < r->nr_analize; i++)
			free(r->analize[i]);
		free(r->analize);
		free(r);
	}
}