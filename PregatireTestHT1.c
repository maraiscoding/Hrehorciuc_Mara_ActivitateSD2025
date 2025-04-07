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
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dim;
};

typedef struct HashTable HashTable;

Carte initializareCarte(int id, float pret, const char* autor, const char* editura) {
	Carte c;
	c.id = id;
	c.pret = pret;
	c.autor = (char*)malloc(sizeof(char) * (strlen(autor) + 1));
	strcpy_s(c.autor, strlen(autor) + 1, autor);
	c.editura = (char*)malloc(sizeof(char) * (strlen(editura) + 1));
	strcpy_s(c.editura, strlen(editura) + 1, editura);
	return c;
}

Carte citireCarteDinFisier(FILE* file) {
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, file);
	char* token;
	Carte c;
	token = strtok(buffer, delimitator);
	c.id = atoi(token);
	c.pret = atof(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	c.autor = (char*)malloc(strlen(token) + 1);
	strcpy_s(c.autor, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	c.editura = (char*)malloc(strlen(token) + 1);
	strcpy_s(c.editura, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return c;
}

void afisareCarte(Carte c) {
	printf("Id:%d\n", c.id);
	printf("Pret:%5.2f\n", c.pret);
	printf("Autor:%s\n", c.autor);
	printf("Editura:%s\n\n", c.editura);
}

void afisareListaCarti(Nod* cap) {
	while (cap) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void afisareTabelaCarti(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		printf("Suntem in clusterul:%d\n", i);
		afisareListaCarti(ht.vector[i]);
	}
}

void adaugaCarteInLista(Nod** cap, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;
	nou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		Nod* p = (*cap);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = NULL;
	}
}

HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < ht.dim; i++) {
		ht.vector[i] = 0;
	}
	return ht;
}

int calculeazaHash(const char* autor, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(autor); i++) {
		suma += autor[i];
	}
	return suma % dimensiune;
}

void inserareCarteInTabela(HashTable hash, Carte carte) {
	if (hash.dim > 0) {
		int pozitie = calculeazaHash(carte.autor, hash.dim);
		if (pozitie < hash.dim) {
			if (hash.vector[pozitie] != NULL) {
				adaugaCarteInLista(&(hash.vector[pozitie]), carte);
			}
			else {
				hash.vector[pozitie] = (Nod*)malloc(sizeof(Nod));
				hash.vector[pozitie]->info = carte;
				hash.vector[pozitie]->next = NULL;
			}
		}
	}
}

HashTable citireCartiDinFisier(const char* numeFisier, int dimensiune) {
	FILE* f = fopen(numeFisier, "r");
	HashTable hash = initializareHashTable(dimensiune);
	while (!feof(f)) {
		inserareCarteInTabela(hash, citireCarteDinFisier(f));
	}
	fclose(f);
	return hash;
}

void dezalocaListaCarti(Nod** cap) {
	Nod* aux = (*cap);
	(*cap) = (*cap)->next;
	free(aux->info.editura);
	free(aux->info.autor);
	free(aux);
}

void dezalocaTabelaCarti(HashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {
		dezalocaListaCarti(&(ht->vector[i]));
	}
	free(ht->vector);
	ht->vector = NULL;
	ht->dim = 0;
}

float calculeazaMedieLista(Nod* lista) {
	float suma = 0;
	int count = 0;
	while (lista) {
		suma += lista->info.pret;
		count++;
		lista = lista->next;
	}
	return suma / count;
}

float* calculeazaPreturiMediiClustere(HashTable ht, int* nrClustere) {
	float* preturi = NULL;
	*nrClustere = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i] != NULL) {
			(*nrClustere)++;
		}
	}
	preturi = (float*)malloc(sizeof(float) * (*nrClustere));
	int contor = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i] != NULL) {
			preturi[contor] = calculeazaMedieLista(ht.vector[i]);
			contor++;
		}
	}
	return preturi;
}

int main() {
	int dimensiune = 7;
	HashTable hash = citireCartiDinFisier("carti.txt", dimensiune);
	afisareTabelaCarti(hash);

	int* nrClustere = 0;
	float* preturi = calculeazaPreturiMediiClustere(hash, &nrClustere);
	printf("Preturile medii per clustere:\n");
	for (int i = 0; i < nrClustere; i++) {
		printf("%5.2f\n", preturi[i]);
	}
}