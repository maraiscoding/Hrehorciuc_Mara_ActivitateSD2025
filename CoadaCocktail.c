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
	Nod* prev;
};

typedef struct ListaDubla ListaDubla;

struct ListaDubla {
	Nod* first;
	Nod* last;
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

void enqueue(ListaDubla* coada, Cocktail cocktail) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = cocktail;
	nou->next = NULL;
	nou->prev = coada->last;
	if (coada->last) {
		coada->last->next = nou;
	}
	else {
		coada->first = nou;
	}
	coada->last = nou;
}

Cocktail dequeue(ListaDubla* coada) {
	if (coada->first) {
		Cocktail c = coada->first->info;
		Nod* temp = coada->first;
		coada->first = coada->first->next;
		free(temp);
		if (coada->first == NULL) {
			coada->last = NULL;
		}
		else {
			coada->first->prev = NULL;
		}
		return c;
	}
	else {
		Cocktail c;
		c.id = -1;
		return c;
	}
}

ListaDubla citireCoadaFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla coada;
	coada.first = NULL;
	coada.last = NULL;
	while (!feof(f)) {
		enqueue(&coada, citesteCocktailDinFisier(f));
	}
	fclose(f);
	return coada;
}

void dezalocaCoada(ListaDubla* coada) {
	while (coada->first) {
		Cocktail c = dequeue(coada);
		free(c.denumire);
		free(c.origine);
	}
}

float calculeazaPretTotal(ListaDubla* coada) {
	ListaDubla temp;
	temp.first = NULL;
	temp.last = NULL;
	float suma = 0;
	while (coada->first) {
		Cocktail c = dequeue(coada);
		suma += c.pret;
		enqueue(&temp, c);
	}
	while (temp.first) {
		enqueue(coada, dequeue(&temp));
	}
	return suma;
}

Cocktail getCocktailById(ListaDubla* coada, int id) {
	ListaDubla temp;
	temp.first = NULL;
	temp.last = NULL;
	Cocktail rezultat = (Cocktail){ -1, 0, 0, NULL, NULL };
	while (coada->first) {
		Cocktail c = dequeue(coada);
		if (c.id == id && rezultat.id == -1) {
			rezultat = c;
		}
		enqueue(&temp, c);
	}
	while (temp.first) {
		enqueue(coada, dequeue(&temp));
	}
	return rezultat;
}

int main() {
	ListaDubla coada = citireCoadaFisier("cocktails.txt");
	Cocktail c1 = dequeue(&coada);
	afisareCocktail(c1);

	Cocktail c2 = getCocktailById(&coada, 2);
	afisareCocktail(c2);

	float total = calculeazaPretTotal(&coada);
	printf("Total:%5.2f\n", total);
}