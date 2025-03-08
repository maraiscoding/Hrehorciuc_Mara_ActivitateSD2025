#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Carte {
	int id;
	char* editura;
	int nrPagini;
};

struct Carte initializare(int id, const char* editura, int nrPagini) {
	struct Carte c;
	c.id = id;
	c.nrPagini = nrPagini;
	if (editura == NULL) {
		c.editura = NULL;
	}
	else {
		c.editura = (char*)malloc(strlen(editura) + 1);
		strcpy_s(c.editura, strlen(editura) + 1, editura);
	}
	return c;
}

void afisare(struct Carte c) {
	printf("\n Cartea cu id-ul %d , de la editura %s are %d pagini ", c.id, c.editura, c.nrPagini);
}

void afisareVector(struct Carte* carte, int nrElemente) {
	if (carte != NULL) {
		for (int i = 0; i < nrElemente; i++) {
			afisare(carte[i]);
			printf("\n");
		}
	}
}

void dezalocare(struct Carte** carte, int* nrElemente) {
	if ((*carte) != NULL) {
		for (int i = 0; i < *nrElemente; i++) {
			free((*carte)[i].editura);
		}
		free(*carte);
		*carte = NULL;
		*nrElemente = 0;
	}
}

void modifica_pagini(struct Carte* c, int nrNou) {
	if (nrNou > 0) {
		c->nrPagini = nrNou;
	}
}

struct Carte* copiazaPrimeleNCarti(struct Carte* carte, int nrElemente, int nrElementeCopiate) {
	if (nrElementeCopiate < nrElemente && nrElementeCopiate>0) {
		struct Carte* carteNoua = (struct Carte*)malloc(nrElementeCopiate * sizeof(struct Carte));
		for (int i = 0; i < nrElementeCopiate; i++) {
			carteNoua[i] = initializare(carte[i].id, carte[i].editura, carte[i].nrPagini);

		}
		return carteNoua;
	}
	else {
		return NULL;
	}
}

void copiazaCartiCuMultePagini(struct Carte* vector, int nrElemente, float prag, struct Carte** vectorNou, int* dimensiune) {
	(*dimensiune) = 0;
	for (char i = 0; i < nrElemente; i++) {
		if (prag < vector[i].nrPagini) {
			(*dimensiune)++;
		}
	}
	if ((*dimensiune) > 0) {
		(*vectorNou) = (struct Carte*)malloc((*dimensiune) * sizeof(struct Carte));
		int k = 0;
		for (int i = 0; i < nrElemente; i++) {
			if (prag < vector[i].nrPagini) {
				(*vectorNou)[k] = vector[i];
				(*vectorNou)[k].editura = malloc(sizeof(char) * (strlen(vector[i].editura) + 1));
				strcpy_s((*vectorNou)[k].editura, strlen(vector[i].editura) + 1, vector[i].editura);
				k++;
			}
		}
	}
}

struct Carte getPrimaCarteDupaConditie(struct Carte* vector, int nrElemente, const char* conditie) {
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].editura, conditie) == 0)
			return vector[i];
	}
	return initializare(-1, 0, NULL, 0, '-');
}

int main() {
	int nrElemente = 3;
	struct Carte* vectorCarti;
	vectorCarti= (struct Carte*)malloc(nrElemente * sizeof(struct Carte));
	vectorCarti[0] = initializare(1, "Adevarul", 302);
	vectorCarti[1] = initializare(1, "Humanitas", 156);
	vectorCarti[2] = initializare(1, "Art", 278);
	printf("Toate cartile:");
	afisareVector(vectorCarti, nrElemente);

	int nrElementeCopiate = 2;
	struct Carte* cartiCopiate = copiazaPrimeleNCarti(vectorCarti, nrElemente, nrElementeCopiate);
	printf("\n\nCartile copiate: ");
	afisareVector(cartiCopiate, nrElementeCopiate);

	struct Carte* cartiCuMultePagini = NULL;
	int nrCartiCuMultePagini = 2;
	copiazaCartiCuMultePagini(vectorCarti, nrElemente,100, &cartiCuMultePagini, &nrCartiCuMultePagini);
	printf("\n\nAfisare carti cu multe pagini:");
	afisareVector(cartiCuMultePagini, nrCartiCuMultePagini);

	struct Carte primaCarte1 = getPrimaCarteDupaConditie(vectorCarti, nrElemente, "Art");
	printf("\nPrima carte:\n");
	afisare(primaCarte1);

	struct Carte primaCarte2 = getPrimaCarteDupaConditie(vectorCarti, nrElemente, "Carturesti");
	printf("\nPrima carte:\n");
	afisare(primaCarte2);
}