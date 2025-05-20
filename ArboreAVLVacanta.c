#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Vacanta {
	int id;
	float pret;
	int nrPersoane;
	char* destinatie;
	char* hotel;
};

typedef struct Vacanta Vacanta;
typedef struct Nod Nod;

struct Nod {
	Vacanta info;
	Nod* st;
	Nod* dr;
	int gradEchilibru;
};


void afiseazaVacanta(Vacanta v) {
	printf("Id:%d\n", v.id);
	printf("Pret:%5.2f\n", v.pret);
	printf("Nr pers:%d\n", v.nrPersoane);
	printf("Destinatie:%s\n", v.destinatie);
	printf("Hotel:%s\n\n", v.hotel);
}

Vacanta citesteVacantaDinFisier(FILE* f) {
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, f);
	char* token;
	Vacanta v;
	token = strtok(buffer, delimitator);
	v.id = atoi(token);
	v.pret = atof(strtok(NULL, delimitator));
	v.nrPersoane = atoi(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	v.destinatie = malloc(strlen(token) + 1);
	strcpy_s(v.destinatie, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	v.hotel = malloc(strlen(token) + 1);
	strcpy_s(v.hotel, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return v;
}

void rotireDreapta(Nod** arbore) {
	Nod* aux = (*arbore)->st;
	(*arbore)->st = aux->dr;
	aux->dr = (*arbore);
	(*arbore) = aux;
	(*arbore)->gradEchilibru++;
}

void rotireStanga(Nod** arbore) {
	Nod* aux = (*arbore)->dr;
	(*arbore)->dr = aux->st;
	aux->st = (*arbore);
	(*arbore) = aux;
	(*arbore)->gradEchilibru--;
}

void adaugaVacantaInArbore(Nod** arbore, Vacanta vacantaNoua) {
	if (!(*arbore)) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = vacantaNoua;
		nou->st = NULL;
		nou->dr = NULL;
		nou->gradEchilibru = 0;
		(*arbore) = nou;
	}
	else {
		if ((*arbore)->info.id <= vacantaNoua.id) {
			adaugaVacantaInArbore(&((*arbore)->dr), vacantaNoua);
			(*arbore)->gradEchilibru--;
		}
		else {
			adaugaVacantaInArbore(&((*arbore)->st), vacantaNoua);
			(*arbore)->gradEchilibru++;
		}
		if ((*arbore)->gradEchilibru == 2) {
			if ((*arbore)->st->gradEchilibru == 1) {
				rotireDreapta(arbore);
			}
			else {
				rotireStanga(&((*arbore)->st));
				rotireDreapta(arbore);
			}
		}
		else if ((*arbore)->gradEchilibru == -2) {
			if ((*arbore)->dr->gradEchilibru != -1) {
				rotireDreapta(&((*arbore)->dr));
			} 
			rotireStanga(arbore);
		}
	}
}

Nod* citesteArboreDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(f)) {
		adaugaVacantaInArbore(&arbore, citesteVacantaDinFisier(f));
	} 
	fclose(f);
	return arbore;
}

void afisarePreordine(Nod* arbore) {
	if (arbore) {
	afiseazaVacanta(arbore->info);
	afisarePreordine(arbore->st);
	afisarePreordine(arbore->dr);
	}
}

int calculInaltime(Nod* arbore) {
	if (arbore) {
		int inaltimeSt = calculInaltime(arbore->st);
		int inaltimeDr = calculInaltime(arbore->dr);
		if (inaltimeSt > inaltimeDr) {
			return 1 + inaltimeSt;
		}
		else {
			return 1 + inaltimeDr;
		}
	}
	return 0;
}

Vacanta getVacantaById(Nod* arbore, int id) {
	Vacanta v;
	v.id = -1;
	if (arbore) {
		if (arbore->info.id < id) {
			return getVacantaById(arbore->dr, id);
		}
		else if (arbore->info.id > id) {
			return getVacantaById(arbore->st, id);
		}
		else {
			return arbore->info;
		}
	}
	return v;
}

int main() {
	Nod* arbore = citesteArboreDinFisier("vacante.txt");
	afisarePreordine(arbore);

	int inaltime = calculInaltime(arbore);
	printf("Inaltime:%d\n", inaltime);

	Vacanta v = getVacantaById(arbore, 1);
	afiseazaVacanta(v);
}