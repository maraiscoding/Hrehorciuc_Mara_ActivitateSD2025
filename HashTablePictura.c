//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h> 
//
//struct Pictura {
//		int id;
//		float pret;
//		int anRealizare;
//		char* centruExpozitie;
//		char* numeAutor;
//};
//
//typedef struct Pictura Pictura;
//typedef struct Nod Nod;
//
//struct Nod {
//	Pictura info;
//	Nod* next;
//};
//
//struct HashTable {
//	Nod** vector;
//	int dim;
//};
//
//typedef struct HashTable HashTable;
//
//Pictura citestePicturaDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Pictura p;
//	token = strtok(buffer, delimitator);
//	p.id = atoi(token);
//	p.pret = atof(strtok(NULL, delimitator));
//	p.anRealizare = atoi(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	p.centruExpozitie = (char*)malloc(strlen(token) + 1);
//	strcpy_s(p.centruExpozitie, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	p.numeAutor = (char*)malloc(strlen(token) + 1);
//	strcpy_s(p.numeAutor, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return p;
//}
//
//void afisarePictura(Pictura p) {
//	printf("Id:%d\n", p.id);
//	printf("Pret:%5.2f\n", p.pret);
//	printf("An realizare:%d\n", p.anRealizare);
//	printf("Centru expozitie:%s\n", p.centruExpozitie);
//	printf("Nume autor:%s\n\n", p.numeAutor);
//}
//
//void afisareListaPicturi(Nod* cap) {
//	while (cap) {
//		afisarePictura(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaInLista(Nod** cap, Pictura picturaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = picturaNoua;
//	nou->next = NULL;
//	if ((*cap) == NULL) {
//		(*cap) = nou;
//	}
//	else {
//		Nod* p = (*cap);
//		while (p->next != NULL) {
//			p = p->next;
//		}
//		p->next = nou;
//	}
//}
//
//HashTable initializareHashTable(int dimensiune) {
//	HashTable ht;
//	ht.dim = dimensiune;
//	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
//	for (int i = 0; i < dimensiune; i++) {
//		ht.vector[i] = NULL;
//	}
//	return ht;
//}
//
//
//int calculeazaHash(const char* nume, int dimensiune) {
//	int suma = 0;
//	for (int i = 0; i < strlen(nume); i++) {
//		suma += nume[i];
//	}
//	return suma % dimensiune;
//}
//
//void insereazaPicturaInTabela(HashTable hash, Pictura pictura) {
//	if (hash.dim > 0) {
//		int pozitie = calculeazaHash(pictura.numeAutor, hash.dim);
//		if (pozitie < hash.dim) {
//			if (hash.vector[pozitie] != NULL) {
//				adaugaInLista(&(hash.vector[pozitie]), pictura);
//			}
//			else {
//				hash.vector[pozitie] = (Nod*)malloc(sizeof(Nod));
//				hash.vector[pozitie]->info = pictura;
//				hash.vector[pozitie]->next = NULL;
//			}
//		}
//	}
//}
//
//HashTable citirePicturiDinFisier(const char* numeF, int dimensiune) {
//	FILE* f = fopen(numeF, "r");
//	HashTable ht = initializareHashTable(dimensiune);
//	while (!feof(f)) {
//		insereazaPicturaInTabela(ht, citestePicturaDinFisier(f));
//	}
//	fclose(f);
//	return ht;
//}
//
//void afisareTabelaPicturi(HashTable ht) {
//	for (int i = 0; i < ht.dim; i++) {
//		printf("\nSuntem pe pozitia:%d\n ", i);
//		afisareListaPicturi(ht.vector[i]);
//	}
//}
//
//
//typedef struct NodDublu NodDublu;
//
//struct NodDublu {
//	Pictura info;
//	NodDublu* prev;
//	NodDublu* next;
//};
//
//struct ListaDubla {
//	NodDublu* prim;
//	NodDublu* ultim;
//};
//
//typedef struct ListaDubla ListaDubla;
//
//void afisareListaDublaPicturiInceput(ListaDubla lista) {
//	NodDublu* p = lista.prim;
//	while (p) {
//		afisarePictura(p->info);
//		p = p->next;
//	}
//}
//
//void adaugaInListaFinal(ListaDubla* lista, Pictura picturaNoua) {
//	NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
//	nou->info = picturaNoua;
//	nou->prev = lista->ultim;
//	nou->next = NULL;
//	if (lista->ultim != NULL) {
//		lista->ultim->next = nou;
//	}
//	else {
//		lista->prim = nou;
//	}
//	lista->ultim = nou;
//}
//
//
//void adaugaPicturiDinHashTableInListaDubla(HashTable hash, ListaDubla* lista) {
//	for (int i = 0; i < hash.dim; i++) {
//		Nod* p = hash.vector[i]; 
//		while (p) {
//			adaugaInListaFinal(lista, p->info);
//			p = p->next; 
//		}
//	}
//}
//
//Nod* extragePicturiDinHashTableInLista(HashTable hash) {
//	Nod* lista = NULL; 
//	for (int i = 0; i < hash.dim; i++) {
//		Nod* p = hash.vector[i];
//		while (p) {
//			adaugaInLista(&lista, p->info); 
//			p = p->next;
//		}
//	}
//	return lista;
//}
// 
//int main() {
//
//	int dimensiune = 7;
//	HashTable hash = citirePicturiDinFisier("picturi.txt", dimensiune);
//	afisareTabelaPicturi(hash);
//		
//	ListaDubla listaDubla = { NULL, NULL };
//	adaugaPicturiDinHashTableInListaDubla(hash, &listaDubla);
//
//	printf("Afisare lista dubla de picturi:\n");
//	afisareListaDublaPicturiInceput(listaDubla);
//
//	Nod* listaSimpla = extragePicturiDinHashTableInLista(hash);
//	printf("\nAfisare lista simpla de picturi:\n");
//	afisareListaPicturi(listaSimpla);
//}