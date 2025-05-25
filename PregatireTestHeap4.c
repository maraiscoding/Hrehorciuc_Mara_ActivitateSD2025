#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Laptop {
	int id;
	float pret;
	char* marca;
	char* procesor;
};

typedef struct Laptop Laptop;
typedef struct Heap Heap;


struct Heap {
	Laptop* vector;
	int lungime;
	int nrLaptopuri;
};


void afiseazaLaptop(Laptop l) {
	printf("Id:%d\n", l.id);
	printf("Pret:%5.2f\n", l.pret);
	printf("Marca:%s\n", l.marca);
	printf("Procesor:%s\n\n", l.procesor);
}

 Laptop citesteLaptopDinFisier(FILE * file) {
		char buffer[100];
		char delimitator[3] = ",\n";
		fgets(buffer, 100, file);
		char* token;
		Laptop l;
		token = strtok(buffer, delimitator);
		l.id = atoi(token);
		l.pret = atof(strtok(NULL, delimitator));
		token = strtok(NULL, delimitator);
		l.marca = (char*)malloc(strlen(token) + 1);
		strcpy_s(l.marca, strlen(token) + 1, token);
		token = strtok(NULL, delimitator);
		l.procesor = (char*)malloc(strlen(token) + 1);
		strcpy_s(l.procesor, strlen(token) + 1, token);
		token = strtok(NULL, delimitator);
		return l;
	}

 Heap initializeazaHeap(int lungime) {
	 Heap h;
	 h.lungime = lungime;
	 h.nrLaptopuri = 0;
	 h.vector = (Laptop*)malloc(sizeof(Laptop) * lungime);
	 return h;
 }

void filtreazaHeap(Heap heap, int pozNod) {
	 int pozSt = 2 * pozNod + 1;
	 int pozDr = 2 * pozNod + 2;
	 int pozMax = pozNod;
	 if (pozSt<heap.nrLaptopuri && heap.vector[pozSt].id>heap.vector[pozMax].id) {
		 pozMax = pozSt;
	 }
	 if (pozDr > heap.nrLaptopuri && heap.vector[pozDr].id > heap.vector[pozMax].id) {
		 pozMax = pozDr;
	 }
	 if (pozMax!= pozNod) {
		 Laptop aux = heap.vector[pozMax];
		 heap.vector[pozMax] = heap.vector[pozNod];
		 heap.vector[pozNod] = aux;
		 if (pozMax < (heap.nrLaptopuri - 2) / 2) {
			 filtreazaHeap(heap, pozMax);
		 }
	 }

 }

Heap citesteHeapFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Heap heap = initializeazaHeap(4);
	while (!feof(f)) {
		heap.vector[heap.nrLaptopuri] = citesteLaptopDinFisier(f);
		heap.nrLaptopuri++;
	}
	fclose(f);
	for (int i = (heap.nrLaptopuri - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afiseazaHeap(Heap heap) {
	if (heap.vector) {
		for (int i = 0; i < heap.nrLaptopuri; i++) {
			afiseazaLaptop(heap.vector[i]);
		}
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i = heap.nrLaptopuri; i < heap.lungime; i++) {
		afiseazaLaptop(heap.vector[i]);
	}
}

void dezalocaHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->vector[i].marca);
		free(heap->vector[i].procesor);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrLaptopuri = 0;
}

Laptop extrageLaptopDinHeap(Heap* heap) {
	if (heap->lungime) {
		Laptop aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrLaptopuri - 1];
		heap->vector[heap->nrLaptopuri - 1] = aux;

		heap->nrLaptopuri--;
		for (int i = (heap->nrLaptopuri - 2) / 2; i >= 0; i--) {
			filtreazaHeap((*heap), i);
		}
		return aux;
	}
	Laptop l;
	l.marca = NULL;
	l.procesor = NULL;
	return l;
}

int main() {
	Heap heap = citesteHeapFisier("laptops.txt");
	afiseazaHeap(heap);
	afiseazaHeapAscuns(heap);

	Laptop l = extrageLaptopDinHeap(&heap);
	afiseazaLaptop(l);
}