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
	Nod* next;
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


void pushStack(Nod** stiva, Cocktail cocktail) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = cocktail;
	nou->next = (*stiva);
	(*stiva) = nou;
}

unsigned char isStackEmpty(Nod* stiva) {
	return stiva == NULL;
}

Cocktail popStack(Nod** stiva) {
	if (*stiva) {
		Nod* temp = (*stiva);
		Cocktail c = temp->info;
		(*stiva) = temp->next;
		free(temp);
		return c;
	}
	else {
		return (Cocktail) { -1, 0, 0, NULL, NULL };
	}
}

Nod* citesteStackDinFisier(const char* numeF) {
	FILE* f = fopen(numeF, "r");
	Nod* stiva = NULL;
	while (!feof(f)) {
		pushStack(&stiva, citesteCocktailDinFisier(f));
	}
	fclose(f);
	return stiva;
}

void dezalocaStiva(Nod** stiva) {
	if (*stiva) {
		Cocktail c = popStack(stiva);
		free(c.denumire);
		free(c.origine);
	}
}

int size(Nod* stiva) {
	int contor = 0;
	while (stiva) {
		contor++;
		stiva = stiva->next;
	}
	return contor;
}

float calculeazaPretTotalStiva(Nod** stiva) {
	Nod* temp = NULL;
	float suma = 0;
	while (!isStackEmpty(*stiva)) {
		Cocktail c = popStack(stiva);
		suma += c.pret;
		pushStack(&temp, c);
	}
	while (!isStackEmpty(temp)) {
		pushStack(stiva, popStack(&temp));
	}
	return suma;
}

Cocktail getCocktailByID(Nod** stiva, int id) {
	Nod* temp = NULL;
	Cocktail rezultat = (Cocktail){ -1, 0, 0, NULL, NULL };
	while (!isStackEmpty(*stiva)) {
		Cocktail c = popStack(stiva);
		if (c.id == id && rezultat.id == -1) {
			rezultat = c;
		}
		pushStack(&temp, c);
	}
	while (!isStackEmpty(temp)) {
		pushStack(stiva, popStack(&temp));
	}
	return rezultat;
}

int main() {
	Nod* stiva = citesteStackDinFisier("cocktails.txt");
	Cocktail c1 = popStack(&stiva);
	afisareCocktail(c1);

	Cocktail c2 = getCocktailByID(&stiva, 2);
	afisareCocktail(c2);

	float total = calculeazaPretTotalStiva(&stiva);
	printf("total:%5.2f\n", total);
}