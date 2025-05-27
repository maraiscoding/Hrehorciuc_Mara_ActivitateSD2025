#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Cocktail {
	int id;
	int nrIngrediente;
	float pret;
	char* denumire;
	char* origine;
};

typedef struct Cocktail Cocktail;
typedef struct Heap Heap;

struct Heap {
	Cocktail* vector;
	int lungime;
	int nrCocktails;
};

void afisareCocktail(Cocktail c) {
	printf("Id:%d\n", c.id);
	printf("Numar ingrediente:%d\n", c.nrIngrediente);
	printf("Pret:%5.2f\n", c.pret);
	printf("Denumire:%s\n", c.denumire);
	printf("Origine:%s\n\n", c.origine);
}

Cocktail citesteCocktailDinFisier(FILE* file) {
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, file);
	char* token;
	Cocktail c;
	token = strtok(buffer, delimitator);
	c.id = atoi(token);
	c.nrIngrediente = atoi(strtok(NULL, delimitator));
	c.pret = atof(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	c.denumire = malloc(strlen(token) + 1);
	strcpy_s(c.denumire, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	c.origine = malloc(strlen(token) + 1);
	strcpy_s(c.origine, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return c;
}

Heap initializareHeap(int lungime) {
	Heap h;
	h.lungime = lungime;
	h.nrCocktails = 0;
	h.vector = (Cocktail*)malloc(sizeof(Cocktail) * lungime);
	return h;
}

void filtreazaHeap(Heap heap, int pozNod) {
	int pozSt = 2 * pozNod + 1;
	int pozDr = 2 * pozNod + 2;
	int pozMax = pozNod;
	if (pozSt<heap.nrCocktails && heap.vector[pozSt].id>heap.vector[pozMax].id) {
		pozMax = pozSt;
	}
	else if (pozDr > heap.nrCocktails && heap.vector[pozDr].id > heap.vector[pozMax].id) {
		pozMax = pozDr;
	}
	if (pozMax != pozNod) {
		Cocktail aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozNod];
		heap.vector[pozNod] = aux;

		if (pozMax < (heap.nrCocktails - 2) / 2) {
			filtreazaHeap(heap, pozMax);
		}
	}
	
}

void afiseazaHeap(Heap heap) {
	if (heap.vector) {
		for (int i = 0; i < heap.nrCocktails; i++) {
			afisareCocktail(heap.vector[i]);
		}
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i = heap.nrCocktails; i < heap.lungime; i++) {
		afisareCocktail(heap.vector[i]);
	}
}

Heap citesteHeapDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Heap heap = initializareHeap(4);
	while (!feof(f)) {
		heap.vector[heap.nrCocktails] = citesteCocktailDinFisier(f);
		heap.nrCocktails++;
	}
	fclose(f);
	for (int i = (heap.nrCocktails - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

Cocktail extrageCocktail(Heap* heap) {
	if (heap->lungime > 0) {
		Cocktail aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrCocktails - 1];
		heap->vector[heap->nrCocktails - 1] = aux;

		heap->nrCocktails--;
		for (int i = (heap->nrCocktails - 2) / 2; i >= 0; i--) {
			filtreazaHeap((*heap), i);
		}
		return aux;
	} 
	Cocktail c;
	c.denumire = NULL;
	c.origine = NULL;
	return c;
}

int main() {
	Heap heap = citesteHeapDinFisier("cocktails.txt");
	afiseazaHeap(heap);

	Cocktail c = extrageCocktail(&heap);
	afisareCocktail(c);
}