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
//
//void dezalocareLD(Lista* lista) {
//	Nod* p = lista->prim;
//	while (p->next != NULL) {
//		free(p->info.numeAutor);
//		free(p->info.centruExpozitie);
//		p = p->next;
//		free(p->prev);
//	}
//	free(p->info.numeAutor);
//	free(p->info.centruExpozitie);
//	free(p);
//	lista->prim = NULL;
//	lista->ultim = NULL;
//}
//
//
//
//char* getCeaMaiScumpaPictura(Lista lista) {
//	if (lista.prim > 0) {
//		Nod* max = lista.prim;
//		Nod* p = lista.prim->next;
//		while (p) {
//			if (p->info.pret > max->info.pret) {
//				max = p;
//			}
//			p = p->next;
//		}
//		char* nume = (char*)malloc(strlen(max->info.numeAutor) + 1);
//		strcpy_s(nume, strlen(max->info.numeAutor) + 1, max->info.numeAutor);
//		return nume;
//	}
//	else {
//		return NULL;
//	}
//}
//
//typedef struct NodSimplu NodSimplu;
//
//struct NodSimplu {
//	Pictura info;
//	struct NodSimplu* next;
//};
//
//void adaugaInListaSimpla(NodSimplu** cap, Pictura picturaNoua) {
//	NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
//	nou->info = picturaNoua;
//	nou->next = NULL;
//
//	if (*cap == NULL) {
//		*cap = nou;
//	}
//	else {
//		NodSimplu* p = *cap;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = nou;
//	}
//}
//
//NodSimplu* copieListaDublaInListaSimpla(Lista lista) {
//	NodSimplu* cap = NULL;
//	Nod* p = lista.prim;
//	while (p) {
//		adaugaInListaSimpla(&cap, p->info);
//		p = p->next;
//	}
//	return cap;
//}
//
//void afisareListaSimpla(NodSimplu* cap) {
//	while (cap) {
//		afisarePictura(cap->info);
//		cap = cap->next;
//	}
//}
// 
//void afisareVectorPicturi(Pictura* picturi, int nrPicturi) {
//	for (int i = 0; i < nrPicturi; i++) {
//		afisarePictura(picturi[i]);
//	}
//}
//
//void adaugaInVector(Pictura** picturi, int* nrPicturi, Pictura picturaNoua) {
//	Pictura* copie;
//	copie = (Pictura*)malloc(sizeof(Pictura) * ((*nrPicturi) + 1));
//	for (int i = 0; i < *nrPicturi; i++) {
//		copie[i] = (*picturi)[i];
//	}
//	copie[*nrPicturi] = picturaNoua; 
//	(*nrPicturi)++;
//	if ((*picturi) != NULL) {
//		free((*picturi));
//	}
//	(*picturi) = copie;
//}
//
//void adaugaPicturiDinListaDublaInVector(Lista lista, Pictura** picturi, int* nrPicturi) {
//	Nod* p = lista.prim;
//	while (p) {
//		adaugaInVector(picturi, nrPicturi, p->info);
//		p = p->next;
//	}
//}
//
//
//int main() {
//	Lista lista;
//	lista = citesteListaDinFisier("picturi.txt");
//	afisareListaDublaPicturiFinal(lista);
//
//	printf("Cea mai scumpa pictura e facuta de: %s\n", getCeaMaiScumpaPictura(lista));
//
//	NodSimplu* listaSimpla = copieListaDublaInListaSimpla(lista);
//	printf("\nAfisare lista simpla:\n");
//	afisareListaSimpla(listaSimpla); 
//
//	Pictura* picturi = NULL;
//	int nrPicturi = 0;
//	adaugaPicturiDinListaDublaInVector(lista, &picturi, &nrPicturi);
//
//	printf("\nAfisare vector picturi:\n");
//	afisareVectorPicturi(picturi, nrPicturi);
//
//	dezalocareLD(&lista);
//}