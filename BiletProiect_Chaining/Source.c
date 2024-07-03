#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Proiect.h"
#include "Chain.h"
#define LINE_SIZE 256

int main() {

    Hash hash = {
        .buckets = NULL,
        .size = HASH_SIZE
    };

    hash.buckets = (Node**)malloc(sizeof(Node*) * HASH_SIZE);
    memset(hash.buckets, 0, sizeof(Node*) * HASH_SIZE);

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
            putHT(hash, proiect);

        }

        display(&hash);

        float suma = bugetTotal(&hash, "Benef2");
        printf("\nBuget: %.2f \n\n", suma);

        changeName(&hash, "Benef2", "Diana");
        display(&hash);

        sterge(&hash, "Diana");
        display(&hash);

    }

}
