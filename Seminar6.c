#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dim;
};

typedef struct HashTable HashTable;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* lista) {
	while (lista) {
		afisareMasina(lista->info);
		lista = lista->next;
	}
}

void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	if ((*lista) == NULL) {
		(*lista) = nou;
	}
	else {
		Nod* p = (*lista);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

int calculeazaHash(char key, int dimensiune) {
	int hash;
	if (dimensiune > 0) {
		hash = key % dimensiune;
		return hash;
	}
	else {
		return 0;
	}
}

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	if (hash.dim > 0) {
		int pozitie = calculeazaHash(masina.serie, hash.dim);
		if (pozitie < hash.dim) {
			if (hash.vector[pozitie] != NULL) {
				//avem coliziune
				adaugaMasinaInLista(&(hash.vector[pozitie]), masina);
			}
			else {
				hash.vector[pozitie] = (Nod*)malloc(sizeof(Nod));
				hash.vector[pozitie]->info = masina;
				hash.vector[pozitie]->next = NULL;
			}
		}
	}
}

HashTable citireMasiniDinFisier(const char* numeFisier, int dimensiune) {
	FILE* f = fopen(numeFisier, "r");
	HashTable hash = initializareHashTable(dimensiune);
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		inserareMasinaInTabela(hash, m);
	}
	fclose(f);
	return hash;
}

void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		printf("\nSuntem pe pozitia %d\n", i);
		afisareListaMasini(ht.vector[i]);
	}
}

void dezalocareListaMasini(Nod** cap) {
	Nod* aux = (*cap);
	(*cap) = (*cap)->next;
	free(aux->info.numeSofer);
	free(aux->info.model);
	free(aux);
}

void dezalocareTabelaDeMasini(HashTable * ht) {
	for (int i = 0; i < ht->dim; i++) {
		dezalocareListaMasini(&(ht->vector[i]));
	}
	free(ht->vector);
	ht->vector = NULL;
	ht->dim = 0;
}

float calculeazaMedieLista(Nod* cap) {
	float suma = 0;
	int nrElemente = 0;
	while (cap) {
		suma += cap->info.pret;
		nrElemente++;
		cap = cap->next;
	}
	return (nrElemente > 0 ? (suma / nrElemente) : 0);
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
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

Masina getMasinaDupaCheie(HashTable ht, char serie) {
	Masina m;
	m.id = -1;
	int pozitie = calculeazaHash(serie, ht.dim);
	if (ht.vector[pozitie] != NULL) {
		Nod* p = ht.vector[pozitie];
		while (p != NULL && p->info.serie != serie) {
			p = p->next;
		}
		if (p) {
			m = p->info;
			m.model = (char*)malloc(strlen(p->info.model) + 1);
			strcpy_s(m.model, strlen(p->info.model)+1, p->info.model);
			m.numeSofer = (char*)malloc(strlen(p->info.numeSofer) + 1);
			strcpy_s(m.numeSofer,strlen(p->info.numeSofer)+1, p->info.numeSofer);
		}
	}
	return m;
}

int main() {
	int dimensiune = 7;
	HashTable hash = citireMasiniDinFisier("masini2.txt", dimensiune);
	afisareTabelaDeMasini(hash);

	int nrClustere = 0;
	float* preturi = calculeazaPreturiMediiPerClustere(hash, &nrClustere);

	printf("Preturile medii per clustere sunt:\n");
	for (int i = 0; i < nrClustere; i++) {
		printf("%.2f  ", preturi[i]);
	}
	printf("\n");

	Masina m = getMasinaDupaCheie(hash, 'A');
	if (m.id != -1) {
		afisareMasina(m);
	}
	else {
		printf("Nu am gasit masina");
	}

	free(m.model);
	free(m.numeSofer);
	return 0;
}