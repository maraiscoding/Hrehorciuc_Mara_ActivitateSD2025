#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Buchet {
	int id;
	float pret;
	char* flori;
	char* florarie;
};

typedef struct Buchet Buchet;
typedef struct Heap Heap;

struct Heap {
	Buchet* vector;
	int lungime;
	int nrBuchete;
};


void afisareBuchet(Buchet b) {
	printf("Id:%d\n", b.id);
	printf("Pret:%5.2f\n", b.pret);
	printf("Flori:%s\n", b.flori);
	printf("Florarie:%s\n\n", b.florarie);
}


Buchet citireBuchetDinFisier(FILE* file) {
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, file);
	char* token;
	Buchet b;
	token = strtok(buffer, delimitator);
	b.id = atoi(token);
	b.pret = atof(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	b.flori = malloc(strlen(token) + 1);
	strcpy_s(b.flori, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	b.florarie = malloc(strlen(token) + 1);
	strcpy_s(b.florarie, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return b;
}

Heap initializareHeap(int lungime) {
	Heap h;
	h.lungime = lungime;
	h.nrBuchete = 0;
	h.vector = (Buchet*)malloc(sizeof(Buchet) * lungime);
	return h;
}

void filtreazaHeap(Heap heap, int pozNod) {
	int pozSt = 2 * pozNod + 1;
	int pozDr = 2 * pozNod + 2;
	int pozMax = pozNod;
	if (pozSt<heap.nrBuchete && heap.vector[pozSt].id>heap.vector[pozMax].id) {
		pozMax = pozSt;
	}
	if (pozDr > pozMax && heap.vector[pozDr].id > heap.vector[pozMax].id) {
		pozMax = pozDr;
	}
	if (pozMax != pozNod) {
		Buchet aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozNod];
		heap.vector[pozNod] = aux;
		if (pozMax < (heap.nrBuchete - 2) / 2) {
			filtreazaHeap(heap, pozMax);
		}
	}
}

Heap citireHeapBucheteFisiere(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Heap heap = initializareHeap(10);
	while (!feof(f)) {
		heap.vector[heap.nrBuchete] = citireBuchetDinFisier(f);
		heap.nrBuchete++;
	}
	fclose(f);
	for (int i = (heap.nrBuchete - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	if (heap.vector) {
		for (int i = 0; i < heap.nrBuchete; i++) {
			afisareBuchet(heap.vector[i]);
		}
	}
}

void afisareElementeAscunse(Heap heap) {
	for (int i = heap.nrBuchete; i < heap.lungime; i++) {
		afisareBuchet(heap.vector[i]);
	}
}

Buchet extragfeBuchet(Heap* heap) {
	if (heap->lungime > 0) {
		Buchet aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrBuchete - 1];
		heap->vector[heap->nrBuchete - 1] = aux;
		heap->nrBuchete--;
		for (int i = (heap->nrBuchete - 2) / 2; i >= 0; i--) {
			filtreazaHeap((*heap), i);
		}
		return aux;
	}
	Buchet b;
	b.flori = NULL;
	b.florarie = NULL;
	return b;
}

void dezalocaHeap(Heap* heap)
{
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->vector[i].flori);
		free(heap->vector[i].florarie);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrBuchete = 0;
}

int main() {
	Heap heap = citireHeapBucheteFisiere("buchete.txt");
	afisareHeap(heap);
}