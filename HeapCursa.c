//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//struct CalCursa {
//	int id;
//	int numarCursa;
//	float pretLicitatie;
//	char* urmatoareaCursa;
//	char* detinator;
//};
//
//
//typedef struct CalCursa Cal;
//
//
//struct Heap {
//	Cal* vector;
//	int nrCai;
//	int lungime;
//};
//
//typedef struct Heap Heap;
//
//Cal citesteCalDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Cal c1;
//	token = strtok(buffer, delimitator);
//	c1.id = atoi(token);
//	c1.numarCursa = atoi(strtok(NULL, delimitator));
//	c1.pretLicitatie = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	c1.urmatoareaCursa = malloc(strlen(token) + 1);
//	strcpy_s(c1.urmatoareaCursa, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	c1.detinator = malloc(strlen(token) + 1);
//	strcpy_s(c1.detinator, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return c1;
//}
//
//void afisareCal(Cal cal) {
//	printf("Id:%d\n", cal.id);
//	printf("Numar cursa:%d\n", cal.numarCursa);
//	printf("Pret licitatie:%5.2f\n", cal.pretLicitatie);
//	printf("Urmatoarea cursa:%s\n", cal.urmatoareaCursa);
//	printf("Detinator:%s\n\n", cal.detinator);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap h;
//	h.lungime = lungime;
//	h.nrCai = 0;
//	h.vector = (Cal*)malloc(sizeof(Cal) * lungime);
//	return h;
//}
//
//void filtreazaHeap(Heap heap, int pozNod) {
//	int pozSt = 2 * pozNod + 1;
//	int pozDr = 2 * pozNod + 2;
//	int pozMax = pozNod;
//	if (pozSt<heap.nrCai && heap.vector[pozSt].id>heap.vector[pozMax].id) {
//		pozMax = pozSt;
//	}
//	if (pozDr > heap.nrCai && heap.vector[pozDr].id > heap.vector[pozMax].id) {
//		pozMax = pozDr;
//	}
//	if (pozMax != pozNod) {
//		Cal aux = heap.vector[pozMax];
//		heap.vector[pozMax] = heap.vector[pozNod];
//		heap.vector[pozNod] = aux;
//		if (pozMax < (heap.nrCai - 2) / 2) {
//			filtreazaHeap(heap, pozMax);
//		}
//	}
//}
//
//Heap citesteHeapDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Heap h = initializareHeap(10);
//	while (!feof(f)) {
//		h.vector[h.nrCai] = citesteCalDinFisier(f);
//		h.nrCai++;
//	}
//	fclose(f);
//	for (int i = (h.nrCai - 2) / 2; i >= 0; i--) {
//		filtreazaHeap(h, i);
//	}
//	return h;
//}
//
//void afisareHeap(Heap heap) {
//	if (heap.vector) {
//		for (int i = 0; i < heap.nrCai; i++) {
//			afisareCal(heap.vector[i]);
//		}
//	}
//}
//
//void afisareHeapAscuns(Heap heap) {
//	for (int i = heap.nrCai; i < heap.lungime; i++) {
//		afisareCal(heap.vector[i]);
//	}
//}
//
//Cal extrageCal(Heap* heap) {
//	if (heap->lungime > 0) {
//		Cal aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrCai - 1];
//		heap->vector[heap->nrCai - 1] = aux;
//
//		heap->nrCai--;
//		for (int i = (heap->nrCai - 2) / 2; i >= 0; i--) {
//			filtreazaHeap((*heap), i);
//		}
//		return aux;
//	}
//	Cal c;
//	c.detinator = NULL;
//	c.urmatoareaCursa = NULL;
//	return c;
//}
//
//void dezalocaHeap(Heap* heap) {
//	for (int i = 0; i < heap->lungime; i++) {
//		free(heap->vector[i].detinator);
//		free(heap->vector[i].urmatoareaCursa);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrCai = 0;
//}
//struct Nod {
//	Cal info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//void inserareInceputInLista(Nod** lista, Cal m) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = m;
//	nou->next = *lista;
//	*lista = nou;
//}
//
//Nod* masiniCuIdMare(Heap* heap, int idMinim) {
//	Nod* lista = NULL;
//	while (heap->vector[0].id >= idMinim) {
//		Cal m = extrageCal(heap);
//		inserareInceputInLista(&lista, m);
//	}
//	return lista;
//}
//
//void afisareLista(Nod* lista) {
//	while (lista) {
//		afisareCal(lista->info);
//		lista = lista->next;
//	}
//}
//
//
//int main() {
//	Heap h = citesteHeapDinFisier("cai.txt");
//	afisareHeap(h);
//
//
//	Nod* lista = masiniCuIdMare(&h, 4);
//		printf("\nLista:\n");
//		afisareLista(lista);
//
//
//		printf("Elementele ascunse:\n");
//		afisareHeapAscuns(h);
//}