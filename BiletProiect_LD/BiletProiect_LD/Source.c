#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "ListaDubla.h"
#include "Proiect.h"
#define LINE_SIZE 256

int main() {

    ListaD* node = NULL; 
    FILE* pFile = fopen("Data.txt", "r");
    if (pFile) {
        char buffer[LINE_SIZE];
        char delimiter[] = ",";
        unsigned int cod;
        char beneficiar[LINE_SIZE];
        char titlu[LINE_SIZE];
        float buget;
        unsigned char exec;

        while (fgets(buffer, sizeof(buffer), pFile)) {
            char* token = strtok(buffer, delimiter);
            cod = atoi(token);

            token = strtok(NULL, delimiter);
            strcpy(titlu, token);

            token = strtok(NULL, delimiter);
            strcpy(beneficiar, token);

            token = strtok(NULL, delimiter);
            exec = (unsigned char)atoi(token);

            token = strtok(NULL, delimiter);
            buget = atof(token);

            Proiect* proiect = createProiect(cod, titlu, beneficiar, exec, buget);
            node = insertTail(node, proiect);
           
        }
     
        display(node);
        printf("\n");
       
        int nr = nrProiecte(node, 4);
        printf("nr Proiecte: %d \n", nr);
        printf("\n");

        schimbaBuget(node, "Benef3", 12);
        display(node);
        printf("\n");

        sortat(&node);
       
        display(node);
        printf("\n");

        int size;
        Proiect** vector = salveazaVector(node, &size, "Benef2");
        afisareVector(vector, size);
    }
   
}
