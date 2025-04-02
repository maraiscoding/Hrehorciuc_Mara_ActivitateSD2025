#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Vacanta {
	int id;
	float pret;
	int nrPers;
	char* destinatie;
	char* hotel;
};

typedef struct Vacanta Vacanta;
typedef struct Nod Nod;

struct Nod {
	Vacanta info;
	Nod* prev;
	Nod* next;
};

struct ListaDubla  {
	Nod* prim;
	Nod* ultim;
};

typedef struct ListaDubla Lista;

void afisareVacanta(Vacanta v) {
	printf("Id:%d\n", v.id);
	printf("Pret:%5.2f\n", v.pret);
	printf("Numar persoane:%d\n", v.nrPers);
	printf("Destinatie:%s\n", v.destinatie);
	printf("Hotel:%s\n\n", v.hotel);
}

void afisareListaVacanteInceput(Lista lista) {
	Nod* p = lista.prim;
	while (p) {
		afisareVacanta(p->info);
		p = p->next;
	}
}

void afisareListaVacanteFinal(Lista lista) {
	Nod* p = lista.ultim;
	while (p) {
		afisareVacanta(p->info);
		p = p->prev;
	}
}

Vacanta citesteVacantaDinFisier(FILE* file) {
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, file);
	char* token;
	Vacanta v;
	token = strtok(buffer, delimitator);
	v.id = atoi(token);
	v.pret = atof(strtok(NULL, delimitator));
	v.nrPers = atoi(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	v.destinatie = malloc(strlen(token) + 1);
	strcpy_s(v.destinatie, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	v.hotel = malloc(strlen(token) + 1);
	strcpy_s(v.hotel, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return v;
}

void adaugaVacantaInListaFinal(Lista* lista, Vacanta vacantaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = vacantaNoua;
	nou->prev = lista->ultim;
	nou->next = NULL;
	if (lista->ultim != NULL) {
		lista->ultim->next = nou;
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;
}

void adaugaVacantaLaInceput(Lista* lista, Vacanta vacantaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = vacantaNoua;
	nou->prev = NULL;
	nou->next = lista->prim;
	if (lista->prim != NULL) {
		lista->prim->prev = nou;
	}
	else {
		lista->ultim = nou;
	}
	lista->prim = nou;
}

Lista citireListaDublaFisier(const char* numeF) {
	FILE* f = fopen(numeF, "r");
	Lista lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	while (!feof(f)) {
		adaugaVacantaLaInceput(&lista, citesteVacantaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareLD(Lista* lista) {
	Nod* p = lista->prim;
	while (p->next != NULL) {
		free(p->info.hotel);
		free(p->info.destinatie);
		p = p->next;
		free(p->prev);
	}
	free(p->info.hotel);
	free(p->info.destinatie);
	free(p);
	lista->prim = NULL;
	lista->ultim = NULL;
}


int main() {
	Lista lista;
	lista = citireListaDublaFisier("vacante.txt");
	afisareListaVacanteFinal(lista);

	dezalocareLD(&lista);
}