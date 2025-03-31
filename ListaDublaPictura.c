//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Pictura {
//	int id;
//	float pret;
//	int anRealizare;
//	char* centruExpozitie;
//	char* numeAutor;
//};
//typedef struct Pictura Pictura;
//typedef struct Nod Nod;
//
//struct Nod {
//	Pictura info;
//	Nod* prev;
//	Nod* next;
//};
//
//struct ListaDubla {
//	Nod* prim;
//	Nod* ultim;
//};
//
//typedef struct ListaDubla Lista;
//
//void afisarePictura(Pictura pictura) {
//	printf("Id:%d\n", pictura.id);
//	printf("Pret:%.2f\n", pictura.pret);
//	printf("An realizare:%d\n", pictura.anRealizare);
//	printf("Centru expozitie:%s\n", pictura.centruExpozitie);
//	printf("Nume autor:%s\n\n", pictura.numeAutor);
//}
//
//void afisareListaDublaPicturiInceput(Lista lista) {
//	Nod* p = lista.prim;
//	while (p) {
//		afisarePictura(p->info);
//		p = p->next;
//	}
//}
//
//Pictura citirePicturaDinFisier(FILE* file) {
//		char buffer[100];
//		char delimitator[3] = ", \n";
//		fgets(buffer, 100, file);
//		char* token;
//		Pictura p;
//		token = strtok(buffer, delimitator);
//		p.id = atoi(token);
//		p.pret = atof(strtok(NULL, delimitator));
//		p.anRealizare = atoi(strtok(NULL, delimitator));
//		token = strtok(NULL, delimitator);
//		p.centruExpozitie = malloc(strlen(token) + 1);
//		strcpy_s(p.centruExpozitie, strlen(token) + 1, token);
//	
//		token = strtok(NULL, delimitator);
//		p.numeAutor = malloc(strlen(token) + 1);
//		strcpy_s(p.numeAutor, strlen(token) + 1, token);
//		token = strtok(NULL, delimitator);
//	
//		return p;
//	}
//
//void afisareListaDublaPicturiFinal(Lista lista) {
//	Nod* p = lista.ultim;
//	while (p) {
//		afisarePictura(p->info);
//		p = p->prev;
//	}
//}
//
//void adaugaInListaFinal(Lista* lista, Pictura picturaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
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
//void adaugaInListaInceput(Lista* lista, Pictura picturaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = picturaNoua;
//	nou->prev = NULL;
//	nou->next = lista->prim;
//	if (lista->prim != NULL) {
//		lista->prim->prev = nou;
//	}
//	else {
//		lista->ultim = nou;
//	}
//	lista->prim = nou;
//}
//
//Lista citesteListaDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Lista lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//	while (!feof(f)) {
//		adaugaInListaFinal(&lista, citirePicturaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//void dezalocare(Lista lista) {
//	Nod* p = lista->prim
//}
//
//int main() {
//	Lista lista;
//	lista = citesteListaDinFisier("picturi.txt");
//	afisareListaDublaPicturiFinal(lista);
//
//}