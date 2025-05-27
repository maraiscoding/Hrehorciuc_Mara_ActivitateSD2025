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
typedef struct Nod Nod;

struct Nod {
	Cocktail info;
	Nod* st;
	Nod* dr;
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

void adaugaCocktailInArbore(Nod** arbore, Cocktail cocktail) {
	if (!(*arbore)) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = cocktail;
		nou->st = NULL;
		nou->dr = NULL;
		(*arbore) = nou;
	}
	else {
		if ((*arbore)->info.id < cocktail.id) {
			adaugaCocktailInArbore(&((*arbore)->dr), cocktail);
		}
		else if ((*arbore)->info.id > cocktail.id) {
			adaugaCocktailInArbore(&((*arbore)->st), cocktail);
		}
	}
}

Nod* citesteArboreFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(f)) {
		adaugaCocktailInArbore(&arbore, citesteCocktailDinFisier(f));
	}
	fclose(f);
	return arbore;
}

void afisareInOrdineSRD(Nod* arbore) {
	if (arbore) {
		afisareInOrdineSRD(arbore->st);
		afisareCocktail(arbore->info);
		afisareInOrdineSRD(arbore->dr);
	}
}

void afisarePreordineRSD(Nod* arbore) {
	if (arbore) {
		afisareCocktail(arbore->info);
		afisarePreordineRSD(arbore->st);
		afisarePreordineRSD(arbore->dr);
	}
}

void afisarePostordineSDR(Nod* arbore) {
	if (arbore) {
		afisarePostordineSDR(arbore->st);
		afisarePostordineSDR(arbore->dr);
		afisareCocktail(arbore->info);
	}
}

void dezalocaArbore(Nod** arbore) {
	if (*arbore) {
		dezalocaArbore(&((*arbore)->st));
		dezalocaArbore(&((*arbore)->dr));
		free((*arbore)->info.denumire);
		free((*arbore)->info.origine);
		free(*arbore);
		(*arbore) = NULL;
	}
}

int determinaNumarNoduri(Nod* arbore) {
	if (arbore) {
		int noduriSt = determinaNumarNoduri(arbore->st);
		int noduriDr = determinaNumarNoduri(arbore->dr);
		return 1 + noduriDr + noduriSt;
	}
	return 0;
}

Cocktail getCocktailByID(Nod* arbore, int id) {
	Cocktail c;
	c.id = -1;
	if (arbore) {
		if (arbore->info.id < id) {
			return getCocktailByID(arbore->dr, id);
		}
		else if (arbore->info.id > id) {
			return getCocktailByID(arbore->st, id);
		}
		else {
			return arbore->info;
		}
	}
	return c;
}

float calculeazaPretTotal(Nod* arbore) {
	if (arbore) {
		float totalSt = calculeazaPretTotal(arbore->st);
		float totalDr = calculeazaPretTotal(arbore->dr);
		return arbore->info.pret + totalSt + totalDr;
	}
	return 0;
}

float calculeazaPretTotalOrigine(Nod* arbore, const char* origine) {
	if (arbore) {
		float totalSt = calculeazaPretTotalOrigine(arbore->st, origine);
		float totalDr = calculeazaPretTotalOrigine(arbore->dr, origine);
		float suma = 0;
		if (strcmp(arbore->info.origine, origine) == 0) {
			suma += arbore->info.pret;
		}
		return suma + totalSt + totalDr;
	}
	return 0;
}

int main() {
	Nod* arbore = citesteArboreFisier("cocktails.txt");
	afisareInOrdineSRD(arbore);

	int noduri = determinaNumarNoduri(arbore);
	printf("NR noduri:%d\n", noduri);


	Cocktail c = getCocktailByID(arbore, 1);
	afisareCocktail(c);

	float total = calculeazaPretTotal(arbore);
	printf("Total:%5.2f\n", total);

	float totalOrigine = calculeazaPretTotalOrigine(arbore, "Spania");
	printf("total origine:%5.2f\n", totalOrigine);
}