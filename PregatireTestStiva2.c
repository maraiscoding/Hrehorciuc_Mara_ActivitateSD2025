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
//    Nod* next;
//};
//
//
//Analiza citesteAnalizaDinFisier(FILE* file) {
//    char buffer[100];
//    char delimitator[3] = ",\n";
//    fgets(buffer, 100, file);
//    char* token;
//    Analiza a;
//    token = strtok(buffer, delimitator);
//    a.id = atoi(token);
//    a.pret = atof(strtok(NULL, delimitator));
//    token = strtok(NULL, delimitator);
//    a.nume = malloc(strlen(token) + 1);
//    strcpy_s(a.nume, strlen(token) + 1, token);
//    token = strtok(NULL, delimitator);
//    a.dataRecoltare = malloc(strlen(token) + 1);
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
//void pushStack(Nod** stiva, Analiza analizaNoua) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = analizaNoua;
//    nou->next = (*stiva);
//    (*stiva) = nou;
//}
//
//Analiza popStack(Nod** stiva) {
//    if (*stiva) {
//        Nod* temp = (*stiva);
//        Analiza a = temp->info;
//        (*stiva) = temp->next;
//        free(temp);
//        return a;
//    }
//    else {
//        return (Analiza){ -1, 0, NULL, NULL };
//    }
//}
//
//Nod* citesteStivaDinFisier(const char* numeFisier) {
//    FILE* f = fopen(numeFisier, "r");
//    Nod* stiva = NULL;
//    while (!feof(f)) {
//        pushStack(&stiva, citesteAnalizaDinFisier(f));
//    }
//    fclose(f);
//    return stiva;
//}
//
//
//void dezalocaStiva(Nod** stiva) {
//    while (*stiva) {
//        Analiza a = popStack(stiva);
//        free(a.nume);
//        free(a.dataRecoltare);
//    }
//}
//
//int size(Nod* stiva) {
//    int contor = 0;
//    while (stiva) {
//        contor++;
//        stiva = stiva->next;
//    }
//    return contor;
//}
//
//
//unsigned char isStackEmpty(Nod* stiva) {
//    return stiva == NULL;
//}
//
//float calculeazaPretStiva(Nod** stiva) {
//    Nod* temp = NULL;
//    float suma = 0;
//    while (!isStackEmpty(*stiva)) {
//        Analiza a = popStack(stiva);
//        suma += a.pret;
//        pushStack(&temp, a);
//    }
//    while (!isStackEmpty(temp)) {
//        pushStack(stiva, popStack(&temp));
//    }
//    return suma;
//}
//
//Analiza getAnalizaById(Nod** stiva, int id) {
//    Nod* temp = NULL;
//    Analiza rezultat = (Analiza){ -1, 0, NULL, NULL };
//    while (!isStackEmpty(*stiva)) {
//        Analiza a = popStack(stiva);
//        if (a.id == id && rezultat.id == -1) {
//            rezultat = a;
//        }
//        pushStack(&temp, a);
//    }
//    while (!isStackEmpty(temp)) {
//        pushStack(stiva, popStack(&temp));
//    }
//    return rezultat;
//}
//
//int main() {
//    Nod* stiva = citesteStivaDinFisier("analize.txt");
//    Analiza a = popStack(&stiva);
//    afisareAnaliza(a);
//
//    float suma = calculeazaPretStiva(&stiva);
//    printf("Suma e:%5.2f\n", suma);
//
//    Analiza a2 = getAnalizaById(&stiva, 1);
//    afisareAnaliza(a2);
//}