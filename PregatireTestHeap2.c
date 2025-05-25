#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct AnalizaMedicala {
    int id;
    float pret;
    char* nume;
    char* dataRecoltare;
};

typedef struct AnalizaMedicala Analiza;
typedef struct Heap Heap;

struct Heap {
    Analiza* vector;
    int nrAnalize;
    int lungime;
};

Analiza citireAnalizeDinFisier(FILE* file) {
    char buffer[100];
    char delimitator[3] = ",\n";
    fgets(buffer, 100, file);
    char* token;
    Analiza a;
    token = strtok(buffer, delimitator);
    a.id = atoi(token);
    a.pret = atof(strtok(NULL, delimitator));
    token = strtok(NULL, delimitator);
    a.nume = (char*)malloc(strlen(token) + 1);
    strcpy_s(a.nume, strlen(token) + 1, token);
    token = strtok(NULL, delimitator);
    a.dataRecoltare = (char*)malloc(strlen(token) + 1);
    strcpy_s(a.dataRecoltare, strlen(token) + 1, token);
    token = strtok(NULL, delimitator);
    return a;
}

void afisareAnaliza(Analiza a) {
    printf("Id:%d\n", a.id);
    printf("Pret:%5.2f\n", a.pret);
    printf("Nume:%s\n", a.nume);
    printf("Data recoltare:%s\n\n", a.dataRecoltare);
}

Heap initializeazaHeap(int lungime) {
    Heap h;
    h.lungime = lungime;
    h.nrAnalize = 0;
    h.vector = (Analiza*)malloc(sizeof(Analiza) * lungime);
    return h;
}

void filtreazaHeap(Heap h, int pozNod) {
    int pozSt = 2 * pozNod + 1;
    int pozDr = 2 * pozNod + 2;
    int pozMax = pozNod;
    if (pozSt<h.nrAnalize && h.vector[pozSt].id>h.vector[pozMax].id) {
        pozMax = pozSt;
    }
    if (pozDr > pozMax && h.vector[pozDr].id > h.vector[pozMax].id) {
        pozMax = pozDr;
    }
    if (pozMax != pozNod) {
        Analiza aux = h.vector[pozMax];
        h.vector[pozMax] = h.vector[pozNod];
        h.vector[pozNod] = aux;
        if (pozMax < (h.nrAnalize - 2) / 2) {
            filtreazaHeap(h, pozMax);
        }
    }
}

Heap citesteHeapDinFisier(const char* numeF) {
    FILE* f = fopen(numeF, "r");
    Heap heap = initializeazaHeap(4);
    while (!feof(f)) {
        heap.vector[heap.nrAnalize] = citireAnalizeDinFisier(f);
        heap.nrAnalize++;
    }
    fclose(f);
    for (int i = (heap.nrAnalize - 2) / 2; i >= 0; i--) {
        filtreazaHeap(heap, i);
    }
    return heap;
}

void afiseazaHeap(Heap heap) {
    if (heap.vector) {
        for (int i = 0; i < heap.nrAnalize; i++) {
            afisareAnaliza(heap.vector[i]);
        }
    }
}

void afiseazaHeapAscuns(Heap heap) {
    for (int i = heap.nrAnalize; i < heap.lungime; i++) {
        afisareAnaliza(heap.vector[i]);
    }
}


Analiza extrageAnaliza(Heap* heap) {
    if (heap->lungime > 0) {
        Analiza aux = heap->vector[0];
        heap->vector[0] = heap->vector[heap->nrAnalize - 1];
        heap->vector[heap->nrAnalize - 1] = aux;

        heap->nrAnalize--;
        for (int i = (heap->nrAnalize - 2) / 2; i >= 0; i--) {
            filtreazaHeap((*heap), i);
        }
        return aux;
    }
    Analiza a;
    a.nume = NULL;
    a.dataRecoltare = NULL;
    return a;
}

void dezalocaHeap(Heap* heap) {
    for (int i = 0; i < heap->lungime; i++) {
        free(heap->vector[i].nume);
        free(heap->vector[i].dataRecoltare);
    }
    free(heap->vector);
    heap->vector = NULL;
    heap->lungime = 0;
    heap->nrAnalize = 0;
}

int main() {
    Heap heap = citesteHeapDinFisier("analize.txt");
    afiseazaHeap(heap);
    afiseazaHeapAscuns(heap);
}