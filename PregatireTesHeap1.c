//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct Carte {
//	int id;
//	float pret;
//	char* autor;
//	char* editura;
//};
//typedef struct Carte Carte;
//typedef struct Heap Heap;
//
//struct Heap {
//	Carte* vector;
//	int lungime;
//	int nrCarti;
//};
//
//Carte citesteCarteDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Carte c;
//	token = strtok(buffer, delimitator);
//	c.id = atoi(token);
//	c.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	c.autor = malloc(strlen(token) + 1);
//	strcpy_s(c.autor, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	c.editura = malloc(strlen(token) + 1);
//	strcpy_s(c.editura, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return c;
//}
//
//void afiseazaCarte(Carte c) {
//	printf("Id:%d\n", c.id);
//	printf("Pret:%5.2f\n", c.pret);
//	printf("Autor:%s\n", c.autor);
//	printf("Editura:%s\n\n", c.editura);
//}
//
//
//Heap initializeazaHeap(int lungime) {
//	Heap h;
//	h.lungime = lungime;
//	h.nrCarti = 0;
//	h.vector = (Carte*)malloc(sizeof(Carte) * lungime);
//	return h;
//}
//
//
//void filtreazaHeap(Heap heap, int pozNod) {
//	int pozSt = 2 * pozNod + 1;
//	int pozDr = 2 * pozNod + 2;
//	int pozMax = pozNod;
//	if (pozSt<heap.nrCarti && heap.vector[pozSt].id>heap.vector[pozMax].id) {
//		pozMax = pozSt;
//	}
//	if (pozDr > heap.nrCarti && heap.vector[pozDr].id > heap.vector[pozMax].id) {
//		pozMax = pozDr;
//	}
//	if (pozMax != pozNod) {
//		Carte aux = heap.vector[pozMax];
//		heap.vector[pozMax] = heap.vector[pozNod];
//		heap.vector[pozNod] = aux;
//		if (pozMax < (heap.nrCarti - 2) / 2) {
//			filtreazaHeap(heap, pozMax);
//		}
//	}
//}
//
//
//Heap citireHeapCartiDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Heap h = initializeazaHeap(4);
//	while (!feof(f)) {
//		h.vector[h.nrCarti] = citesteCarteDinFisier(f);
//		h.nrCarti++;
//	}
//	fclose(f);
//	for (int i = (h.nrCarti - 2) / 2; i >= 0; i--) {
//		filtreazaHeap(h, i);
//	}
//	return h;
//}
//
//void afiseazaHeap(Heap heap) {
//	if (heap.vector) {
//		for (int i = 0; i < heap.nrCarti; i++) {
//			afiseazaCarte(heap.vector[i]);
//		}
//}
//}
//
//void afiseazaAscuns(Heap heap) {
//	for (int i = heap.nrCarti; i < heap.lungime; i++) {
//		afiseazaCarte(heap.vector[i]);
//	}
//}
//
//Carte extrageCarte(Heap* heap) {
//	if (heap->lungime > 0) {
//		Carte aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrCarti - 1];
//		heap->vector[heap->nrCarti - 1] = aux;
//
//		heap->nrCarti--;
//		for (int i = (heap->nrCarti - 2) / 2; i >= 0; i--) {
//			filtreazaHeap((*heap), i);
//		}
//		return aux;
//	}
//	Carte c;
//	c.autor = NULL;
//	c.editura = NULL;
//	return c;
//}
//
//void dezalocaHeap(Heap* heap) {
//	for (int i = 0; i < heap->lungime; i++) {
//		free(heap->vector[i].autor);
//		free(heap->vector[i].editura);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrCarti = 0;
//}
//
//int main() {
//	Heap heap = citireHeapCartiDinFisier("carti.txt");
//	afiseazaHeap(heap);
//
//	Carte c = extrageCarte(&heap);
//	printf("Prima masina extrasa:");
//	afiseazaCarte(c);
//
//	printf("Elem ascunse:");
//	afiseazaAscuns(heap);
//
//
//}