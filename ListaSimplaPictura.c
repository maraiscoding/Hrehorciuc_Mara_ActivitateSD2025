#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pictura {
	int id;
	float pret;
	int anRealizare;
	char* centruExpozitie;
	char* numeAutor;
};
typedef struct Pictura Pictura;
typedef struct Nod Nod;

struct Nod {
	Pictura info;
	Nod* next;
};



Pictura citirePicturaDinFisier(FILE* file) {
	char buffer[100];
	char delimitator[3] = ", \n";
	fgets(buffer, 100, file);
	char* token;
	Pictura p;
	token = strtok(buffer, delimitator);
	p.id = atoi(token);
	p.pret = atof(strtok(NULL, delimitator));
	p.anRealizare = atoi(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	p.centruExpozitie = malloc(strlen(token) + 1);
	strcpy_s(p.centruExpozitie, strlen(token) + 1, token);

	token = strtok(NULL, delimitator);
	p.numeAutor = malloc(strlen(token) + 1);
	strcpy_s(p.numeAutor, strlen(token) + 1, token);

	return p;
}

void afisarePictura(Pictura pictura) {
	printf("Id:%d\n", pictura.id);
	printf("Pret:%.2f\n", pictura.pret);
	printf("An realizare:%d\n", pictura.anRealizare);
	printf("Centru expozitie:%s\n", pictura.centruExpozitie);
	printf("Nume autor:%s\n\n", pictura.numeAutor);
}

void afisareListaPicturi(Nod* cap) {
	while (cap) {
		afisarePictura(cap->info);
		cap = cap->next;
	}
}

void adaugaPicturaLaFinal(Nod** cap, Pictura picturaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = picturaNoua;
	nou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		Nod* p = (*cap);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}

void adaugaPicturaLaInceput(Nod** cap, Pictura picturaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = picturaNoua;
	nou->next = cap;
	(*cap) = nou;
}

Nod* citireListaPicturiDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaPicturaLaFinal(&lista, citirePicturaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareListaPicturi(Nod** cap) {
	while ((*cap) != NULL) {
		Nod* aux = (*cap);
		*cap = (*cap)->next;
		free(aux->info.numeAutor);
		free(aux->info.centruExpozitie);
		free(aux);
	}
}

int main() {
	Nod* cap = NULL;
	cap = citireListaPicturiDinFisier("picturi.txt");
	afisareListaPicturi(cap);
}