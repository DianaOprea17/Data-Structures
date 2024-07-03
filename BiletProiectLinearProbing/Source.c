#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Proiect.h"
#include "LinearProbing.h"
#define LINE_SIZE 256

int main() 
{
    Hash hash = {
        .items = NULL,
        .size = 0
    };
 

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
            // printProiect(proiect);
            putHT(&hash, proiect);

        }

        display(&hash);
        float suma = sumaBuget(&hash, "Benef2");
        printf("\nBuget: %.2f \n", suma);

        modifBenef(&hash, "Benef2", "Diana");
        display(&hash);
    }

}
