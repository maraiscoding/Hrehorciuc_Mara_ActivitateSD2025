#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

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
	//afiseaza toate atributele unei masini
	printf("Masina cu id-ul %d, numarul de usi %d, pretul %.2f, modelul %s, numeLe soferului %s, seria%c\n ",
		masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
	if (masini != NULL) {
		for (int i = 0; i < nrMasini; i++)
			afisareMasina(masini[i]);
		printf("\n");
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	//Masina** masini-adresa adresei, pt a putea modifica
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;
    Masina* copie;
	copie =(Masina*)malloc(sizeof(Masina) * ((*nrMasini)+1));
	for (int i = 0; i < (*nrMasini) - 1; i++) {
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
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
	char buffer[100];
	fgets(buffer, 100, file);
	Masina masina;
	char delimitator[3] = ",\n";
	char* token;
	token = strtok(buffer, delimitator);
	masina.id = atoi(token);
	token = strtok(NULL, delimitator);
	masina.nrUsi = atoi(token);
	token = strtok(NULL, delimitator);
	masina.pret = atof(token);
	token = strtok(NULL, delimitator);
	masina.model = (char*)malloc(strlen(token) + 1);
	strcpy_s(masina.model, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	masina.numeSofer = (char*)malloc(strlen(token) + 1);
	strcpy_s(masina.numeSofer, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	masina.serie = *strtok(NULL,delimitator);
	return masina;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	Masina* masini = NULL;
	do {
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
	} while (!feof(file));
	fclose(file);
	return masini;
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
	int dim = 0;
    masini = citireVectorMasiniFisier("masini.txt", &dim);
	afisareVectorMasini(masini, dim);	

	float medie = pretMediuDupaNrUsi(masini, dim, 5);
	printf("Media este:", medie);
	return 0;
}