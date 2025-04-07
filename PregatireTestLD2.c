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
//    Nod* prim;
//    Nod* ultim;
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
//void afisareListaDubla(Lista lista) {
//    Nod* p = lista.prim;
//    while (p) {
//        afisareAnaliza(p->info);
//        p = p->next;
//    }
//}
//
//void adaugaInListaDublaFinal(Lista* lista, Analiza analizaNoua) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = analizaNoua;
//    nou->next = NULL;
//    nou->prev = lista->ultim;
//    if (lista->ultim != NULL) {
//        lista->ultim->next = nou;
//    }
//    else {
//        lista->prim = nou;
//    }
//    lista->ultim = nou;
//}
//
//void adaugaInListaDublaInceput(Lista* lista, Analiza analizaNoua) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = analizaNoua;
//    nou->prev = NULL;
//    nou->next = lista->prim;
//    if (lista->prim != NULL) {
//        lista->prim->prev = nou;
//    }
//    else {
//        lista->ultim = nou;
//    }
//    lista->prim = nou;
//}
//
//Lista citesteListaDublaAnalize(const char* numeFisier) {
//    FILE* f = fopen(numeFisier, "r");
//    Lista lista;
//    lista.prim = NULL;
//    lista.ultim = NULL;
//    while (!feof(f)) {
//        adaugaInListaDublaFinal(&lista, citireAnalizeDinFisier(f));
//    }
//    fclose(f);
//    return lista;
//}
//
//void dezalocareLD(Lista* lista) {
//    Nod* p = lista->prim;
//    while (p->next != NULL) {
//        free(p->info.dataRecoltare);
//        free(p->info.nume);
//        p = p->next;
//        free(p->prev);
//    } 
//    free(p->info.dataRecoltare);
//    free(p->info.nume);
//    free(p);
//    lista->prim = NULL;
//    lista->ultim = NULL;
//}
//
//float calculeazaPretMediu(Lista lista) {
//    Nod* aux = lista.prim;
//    float suma = 0;
//    int count = 0;
//    while (aux) {
//        suma += aux->info.pret;
//        count++;
//        aux = aux->next;
//    }
//    return suma / count;
//}
//
//char* getCeaMaiScumpaAnaliza(Lista lista) {
//    if (lista.prim) {
//        Nod* max = lista.prim;
//        Nod* p = lista.prim->next;
//        while (p) {
//            if (p->info.pret > max->info.pret) {
//                max = p;
//            }
//            p = p->next;
//        }
//        char* nume = (char*)malloc(strlen(max->info.nume) + 1);
//        strcpy_s(nume, strlen(max->info.nume) + 1, max->info.nume);
//        return nume;
//    }
//    else {
//        return NULL;
//    }
//}
//
//int main() {
//    Lista lista;
//    lista = citesteListaDublaAnalize("analize.txt");
//    afisareListaDubla(lista);
//
//    printf("Pretul mediu este:%5.2f\n", calculeazaPretMediu(lista));
//}