#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

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
	Nod* nodSt;
	Nod* nodDr;
};

void afiseazaPictura(Pictura p) {
	printf("Id:%d\n", p.id);
	printf("Pret:%5.2f\n", p.pret);
	printf("An realizare:%d\n", p.anRealizare);
	printf("Centru expozitie:%s\n", p.centruExpozitie);
	printf("Nume autor:%s\n\n", p.numeAutor);
}

Pictura citestePicturaDinFisier(FILE* file) {
	char buffer[100];
	char delimitator[3] = ",\n";
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
	p.numeAutor= malloc(strlen(token) + 1);
	strcpy_s(p.numeAutor, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return p;
}


void adaugaPicturaInArbore(Nod** arbore, Pictura picturaNoua) {
	if (!(*arbore)) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = picturaNoua;
		nou->nodSt = NULL;
		nou->nodDr = NULL;
		(*arbore) = nou;
	}
	else {
		if ((*arbore)->info.id > picturaNoua.id) {
			adaugaPicturaInArbore(&(*arbore)->nodSt, picturaNoua);
		}
		else if ((*arbore)->info.id < picturaNoua.id) {
			adaugaPicturaInArbore(&(*arbore)->nodDr, picturaNoua);
		}
	}
}

Nod* citesteArboreDePicturiDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(f)) {
		adaugaPicturaInArbore(&arbore, citestePicturaDinFisier(f));
	}
	fclose(f);
	return arbore;
}

void afiseazaInOrdineSRD(Nod* arbore) {
	if (arbore) {
		afiseazaInOrdineSRD(arbore->nodSt);
		afiseazaPictura(arbore->info);
		afiseazaInOrdineSRD(arbore->nodDr);
	}
}

void afiseazaPreordineRSD(Nod* arbore) {
	if (arbore) {
		afiseazaPictura(arbore->info);
		afiseazaPreordineRSD(arbore->nodSt);
		afiseazaPreordineRSD(arbore->nodDr);
	}
}

void afiseazaPostordineSDR(Nod* arbore) {
	if (arbore) {
		afiseazaPostordineSDR(arbore->nodSt);
		afiseazaPostordineSDR(arbore->nodDr);
		afiseazaPictura(arbore->info);
	}
}

void dezalocaArborePicturi(Nod** arbore) {
	if (*arbore) {
		dezalocaArborePicturi(&(*arbore)->nodSt);
		dezalocaArborePicturi(&(*arbore)->nodDr);
		free((*arbore)->info.centruExpozitie);
		free((*arbore)->info.numeAutor);
		free(*arbore);
		*arbore = NULL;
	}
}

Pictura getPicturaById(Nod* arbore, int id) {
	Pictura p;
	p.id = -1;
	if (arbore) {
		if (arbore->info.id < id) {
			return getPicturaById(arbore->nodDr, id);
		}
		else if (arbore->info.id > id) {
			return getPicturaById(arbore->nodSt, id);
		}
		else {
			return arbore->info;
		}
	}
	return p;
}

int determinaNumarNoduri(Nod* arbore) {
	if (arbore) {
		int noduriSt = determinaNumarNoduri(arbore->nodSt);
		int noduriDr = determinaNumarNoduri(arbore->nodDr);
		return 1 + noduriSt + noduriDr;
	}
	return 0;
}

float calculeazaPretTotal(Nod* arbore) {
	if (arbore) {
		float totalSt = calculeazaPretTotal(arbore->nodSt);
		float totalDr = calculeazaPretTotal(arbore->nodDr);
		return arbore->info.pret + totalSt + totalDr;
	}
	return 0;
}

float calculeazaPretulPicturilorUnuiAutor(Nod* arbore, const char* numeAutor) {
	if (arbore) {
		float totalSt = calculeazaPretulPicturilorUnuiAutor(arbore->nodSt, numeAutor);
		float totalDr = calculeazaPretulPicturilorUnuiAutor(arbore->nodDr, numeAutor);
		float sumaCrt = 0;
		if (strcmp(arbore->info.numeAutor, numeAutor) == 0) {
			sumaCrt += arbore->info.pret;
		}
		return sumaCrt + totalSt + totalDr;
	}
	return 0;
}

int main() {
	Nod* radacina = citesteArboreDePicturiDinFisier("picturi.txt");
	printf("Afisare in ordine: \n");
	afiseazaInOrdineSRD(radacina);
	printf("\nAfisare preordine: \n");
	afiseazaPreordineRSD(radacina);
	printf("\nAfisare postordine: \n");
	afiseazaPostordineSDR(radacina);
}