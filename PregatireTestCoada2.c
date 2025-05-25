//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct AnalizaMedicala {
//    int id;
//    float pret;
//    char* nume;
//    char* dataRecoltare;
//};
//
//typedef struct AnalizaMedicala Analiza;
//typedef struct Nod Nod;
//
//struct Nod {
//    Analiza info;
//    Nod* prev;
//    Nod* next;
//};
//
//struct ListaDubla {
//    Nod* first;
//    Nod* last;
//};
//
//typedef struct ListaDubla Lista;
//
//Analiza citireAnalizeDinFisier(FILE* file) {
//    char buffer[100];
//    char delimitator[3] = ",\n";
//    fgets(buffer, 100, file);
//    char* token;
//    Analiza a;
//    token = strtok(buffer, delimitator);
//    a.id = atoi(token);
//    a.pret = atof(strtok(NULL, delimitator));
//    token = strtok(NULL, delimitator);
//    a.nume = (char*)malloc(strlen(token) + 1);
//    strcpy_s(a.nume, strlen(token) + 1, token);
//    token = strtok(NULL, delimitator);
//    a.dataRecoltare = (char*)malloc(strlen(token) + 1);
//    strcpy_s(a.dataRecoltare, strlen(token) + 1, token);
//    token = strtok(NULL, delimitator);
//    return a;
//}
//
//void afisareAnaliza(Analiza a) {
//    printf("Id:%d\n", a.id);
//    printf("Pret:%5.2f\n", a.pret);
//    printf("Nume:%s\n", a.nume);
//    printf("Data recoltare:%s\n\n", a.dataRecoltare);
//}
//
//
//void enqueue(Lista* coada, Analiza analiza) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = analiza;
//    nou->next = NULL;
//    nou->prev = coada->last;
//    if (coada->last) {
//        coada->last->next = NULL;
//    }
//    else {
//        coada->first = NULL;
//    }
//    coada->last = NULL;
//}
//
//Analiza dequeue(Lista* coada) {
//    if (coada->first) {
//        Analiza a = coada->first->info;
//        Nod* temp = coada->first;
//        coada->first = coada->first->next;
//        free(temp);
//        if (coada->first == NULL) {
//            coada->last = NULL;
//        }
//        else {
//            coada->first->prev = NULL;
//        }
//        return a;
//
//    }
//    else {
//        Analiza a;
//        a.id = -1;
//        return a;
//    }
//}
//
//Lista citireCoadaAnalizeFisier(const char* numeFisier) {
//    FILE* f = fopen(numeFisier, "r");
//    Lista coada;
//    coada.first = NULL;
//    coada.last = NULL;
//    while (!feof(f)) {
//        enqueue(&coada, citireAnalizeDinFisier(f));
//    }
//    fclose(f);
//    return coada;
//}