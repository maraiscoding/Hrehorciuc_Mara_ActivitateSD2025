#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Carte {
	int id;
	float pret;
	char* autor;
	char* editura;
};
typedef struct Carte Carte;
typedef struct Nod Nod;

struct Nod {
	Carte info;
	Nod* prev;
	Nod* next;
};


typedef struct ListaDubla ListaDubla;

struct ListaDubla {
	Nod* first;
	Nod* last;
};

Carte citesteCarteDinFisier(FILE* file) {
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, file);
	char* token;
	Carte c;
	token = strtok(buffer, delimitator);
	c.id = atoi(token);
	c.pret = atof(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	c.autor = malloc(strlen(token) + 1);
	strcpy_s(c.autor, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	c.editura = malloc(strlen(token) + 1);
	strcpy_s(c.editura, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return c;
}

void afiseazaCarte(Carte c) {
	printf("Id:%d\n", c.id);
	printf("Pret:%5.2f\n", c.pret);
	printf("Autor:%s\n", c.autor);
	printf("Editura:%s\n\n", c.editura);
}


void enqueue(ListaDubla* coada, Carte carte) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carte;
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

Carte dequeue(ListaDubla* coada) {
	if (coada->first) {
		Carte c = coada->first->info;
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
		Carte c;
		c.id = -1;
		return c;
	}
}

ListaDubla citireCoadaCartiFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla coada;
	coada.first = NULL;
	coada.last = NULL;
	while (!feof(f)) {
		enqueue(&coada, citesteCarteDinFisier(f));
	}
	fclose(f);
	return coada;
}

void dezalocaCoada(ListaDubla* coada) {
	while (coada->first) {
		Carte c = dequeue(coada);
		free(c.autor);
		free(c.editura);
	}
}

float calculeazaPretTotal(ListaDubla* coada) {
	ListaDubla temp;
	temp.first = NULL;
	temp.last = NULL;
	float suma = 0;
	while (coada->first) {
		Carte c = dequeue(coada);
		suma += c.pret;
		enqueue(&temp, c);
	}
	while (temp.first) {
		enqueue(coada, dequeue(&temp));
	}
	return suma;
}

Carte getCarteById(ListaDubla* coada, int id) {
	ListaDubla temp;
	temp.first = NULL;
	temp.last = NULL;
	Carte rezultat = (Carte){ -1, 0, NULL, NULL };
	while (coada->first) {
		Carte c = dequeue(coada);
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
	ListaDubla coada = citireCoadaCartiFisier("carti.txt");
	Carte c1 = dequeue(&coada);
	afiseazaCarte(c1);


	Carte c2 = getCarteById(&coada, 2);
	afiseazaCarte(c2);

	float suma = calculeazaPretTotal(&coada);
	printf("Suma e: %5.2f\n", suma);
}
