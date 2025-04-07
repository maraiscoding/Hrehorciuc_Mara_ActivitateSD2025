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
//Analiza initializareAnaliza(int id, float pret, const char* nume, const char* dataRecoltare) {
//    Analiza a;
//    a.id = id;
//    a.pret = pret;
//    a.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
//    strcpy_s(a.nume, strlen(nume) + 1, nume);
//    a.dataRecoltare = (char*)malloc(sizeof(char) * (strlen(dataRecoltare) + 1));
//    strcpy_s(a.dataRecoltare, strlen(dataRecoltare) + 1, dataRecoltare);
//    return a;
//}
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
//void afisareListaAnalize(Nod* cap) {
//    while (cap) {
//        afisareAnaliza(cap->info);
//        cap = cap->next;
//    }
//}
//
//void adaugaInListaFinal(Nod** cap, Analiza analizaNoua) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = analizaNoua;
//    nou->next = NULL;
//    if ((*cap) == NULL) {
//        (*cap) = nou;
//    }
//    else {
//        Nod* p = (*cap);
//        while (p->next != NULL) {
//            p = p->next;
//        }
//        p->next = nou;
//    }
//}
//
//void adaugaInListaInceput(Nod** cap, Analiza analizaNoua) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = analizaNoua;
//    nou->next = (*cap);
//    (*cap) = nou;
//}
//
//Nod* citesteListaAnalizeDinFisier(const char* numeFisier) {
//    FILE* f = fopen(numeFisier, "r");
//    Nod* lista = NULL;
//    while (!feof(f)) {
//        adaugaInListaInceput(&lista, citireAnalizeDinFisier(f));
//    }
//    fclose(f);
//    return lista;
//}
//
//float calculeazaPretMediu(Nod* lista) {
//    if (!lista) {
//        return 0;
//    }
//    float suma = 0;
//    int count = 0;
//    while (lista) {
//        suma += lista->info.pret;
//        count++;
//        lista = lista->next;
//    }
//    return suma / count;
//}
//
//char* getAnalizaScumpa(Nod* lista) {
//    float pretulMaxim = 0;
//    char* numeScump = NULL;
//    while (lista) {
//        if (lista->info.pret > pretulMaxim) {
//            pretulMaxim = lista->info.pret;
//            numeScump = lista->info.nume;
//        }
//        lista = lista->next;
//    }
//    if (pretulMaxim > 0) {
//        char* nou = (char*)malloc(strlen(numeScump) + 1);
//        strcpy_s(nou, strlen(numeScump) + 1, numeScump);
//        return nou;
//    }
//    else {
//        return NULL;
//    }
//}
//void dezalocare(Nod** cap) {
//    Nod* aux = (*cap);
//    (*cap) = (*cap)->next;
//    free(aux->info.dataRecoltare);
//    free(aux->info.nume);
//    free(aux);
//}
//
//int main() {
//   /* Nod* cap = NULL;
//    cap = citesteListaAnalizeDinFisier("analize.txt");
//    afisareListaAnalize(cap);
//
//    printf("Pretul mediu este:%5.2f\n", calculeazaPretMediu(cap));
//    printf("Cea mai scumpa analiza este:%s\n", getAnalizaScumpa(cap));*/
//
//
//    Nod* cap1 = NULL;
//    Analiza a1 = initializareAnaliza(23, 45.00, "amilaza", "6.04.2025");
//    Analiza a2 = initializareAnaliza(24, 34.00, "colesterol", "6.04.2025");
//    adaugaInListaFinal(&cap1, a1);
//    adaugaInListaFinal(&cap1, a2);
//    afisareListaAnalize(cap1);
//
//
//   /* dezalocare(&cap);*/
//}