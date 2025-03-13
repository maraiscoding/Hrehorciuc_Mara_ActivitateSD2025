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

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr usi: %d\n", masina.nrUsi);
	printf("Pret: %5.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
		for (int i = 0; i < nrMasini; i++)
			afisareMasina(masini[i]);
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
    Masina* copie;
	copie =(Masina*)malloc(sizeof(Masina) * ((*nrMasini)+1));
	for (int i = 0; i < *nrMasini; i++) {
		copie[i] = (*masini)[i];
	}
	copie[*nrMasini] = masinaNoua; //il adaugam ca ultim element in copie
	(*nrMasini)++;
	if ((*masini) != NULL) {
		free((*masini));
	}
	(*masini) = copie;
}

Masina citireMasinaFisier(FILE* file) {
	Masina m;
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, file);
	char* token;
	token = strtok(buffer, delimitator);
	m.id = atoi(token);
	m.nrUsi = atoi(strtok(NULL, delimitator));
	m.pret = atof(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	m.model = malloc(sizeof(char) * (strlen(token) + 1));
	strcpy_s(m.model, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	m.numeSofer = malloc(sizeof(char) * (strlen(token) + 1));
	strcpy_s(m.numeSofer, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	m.serie = token[0];
	return m;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* file = fopen(numeFisier, "r");
	if (!file) {
		printf("Eroare: Nu s-a putut deschide fisierul %s\n", numeFisier);
		return NULL;
	}
	else {
		Masina* masini = NULL;
		do {
			adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
		} while (!feof(file));
		fclose(file);
		return masini;
	}
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
	if ((*vector) != NULL) {
		for (int i = 0; i < *nrMasini; i++) {
			free((*vector)[i].numeSofer);
			free((*vector)[i].model);
		}
		free(*vector);
		*vector = NULL;
		*nrMasini = 0;
	}
}

float pretMediuDupaNrUsi(Masina* vector, int nrMasini, int nrUsi) {
	float suma = 0;
	int index = 0;
	for (int i = 0; i < nrMasini; i++) {
		if (vector[i].nrUsi == nrUsi) {
			suma += vector[i].pret;
			index++;
		}
	}
	if (index > 0) {
		return suma / index;
	}
		return 0;
}

int main() {
	Masina* masini = NULL;
	int nrMasini = 0;
    masini = citireVectorMasiniFisier("masini1.txt", &nrMasini);
	afisareVectorMasini(masini, nrMasini);	

	float medie = pretMediuDupaNrUsi(masini, nrMasini, 5);
	printf("Media este:%5.2f\n", medie);
	return 0;
}