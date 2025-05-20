#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct Pictura {
	int id;
	float pret;
	char* centruExpozitie;
	char* numeAutor;
};
typedef struct Pictura Pictura;
typedef struct Nod Nod;

struct Nod {
	Pictura info;
	Nod* st;
	Nod* dr;
	int gradEchilibru;
};

void afiseazaPictura(Pictura p) {
	printf("Id:%d\n", p.id);
	printf("Pret:%5.2f\n", p.pret);
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
	token = strtok(NULL, delimitator);
	p.centruExpozitie = malloc(strlen(token) + 1);
	strcpy_s(p.centruExpozitie, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	p.numeAutor = malloc(strlen(token) + 1);
	strcpy_s(p.numeAutor, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return p;
}

void rotireStanga(Nod** arbore) {
	Nod* aux = (*arbore)->dr;
	(*arbore)->dr = aux->st;
	aux->st = (*arbore);
	(*arbore) = aux;
	(*arbore)->gradEchilibru--;
}

void rotireDreapta(Nod** arbore) {
	Nod* aux = (*arbore)->st;
	(*arbore)->st = aux->dr;
	aux->dr = (*arbore);
	(*arbore) = aux;
	(*arbore)->gradEchilibru++;
}

void adaugaPicturaInArbore(Nod** arbore, Pictura picturaNoua) {
	if (!(*arbore)) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = picturaNoua;
		nou->st = NULL;
		nou->dr = NULL;
		nou->gradEchilibru = 0;
		(*arbore) = nou;
	}
	else {
		if ((*arbore)->info.id <= picturaNoua.id) {
			adaugaPicturaInArbore(&((*arbore)->dr), picturaNoua);
			(*arbore)->gradEchilibru--;
		}
		else {
			adaugaPicturaInArbore(&((*arbore)->st), picturaNoua);
			(*arbore)->gradEchilibru++;
		}
	if ((*arbore)->gradEchilibru == 2) {
		if ((*arbore)->st->gradEchilibru == 1) {
			rotireDreapta(arbore);
		}
		else {
			rotireStanga(&((*arbore)->st));
			rotireDreapta(arbore);
		}
	}
	else if ((*arbore)->gradEchilibru == -2) {
		if ((*arbore)->dr->gradEchilibru != -1) {
			rotireDreapta(&((*arbore)->dr));
		}
		rotireStanga(arbore);
	}
}
}

void afiseazaPreordine(Nod* arbore) {
	if (arbore) {
		afiseazaPictura(arbore->info);
		afiseazaPreordine(arbore->st);
		afiseazaPreordine(arbore->dr);
	}
}

Nod* citesteArboreDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(f)) {
		adaugaPicturaInArbore(&arbore, citestePicturaDinFisier(f));
	}
	fclose(f);
	return arbore;
}

int calculInaltime(Nod* radacina) {
	if (radacina) {
		int inaltimeSt = calculInaltime(radacina->st);
		int inaltimeDr = calculInaltime(radacina->dr);
		if (inaltimeSt > inaltimeDr) {
			return 1 + inaltimeSt;
		}
		else {
			return 1 + inaltimeDr;
		}
	}
	else {
		return 0;
	}

}

void dezalocaArbore(Nod** arbore) {
	if (*arbore) {
		dezalocaArbore(&(*arbore)->st);
		dezalocaArbore(&(*arbore)->dr);
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
			return getPicturaById(arbore->dr, id);
		}
		else if (arbore->info.id > id) {
			return getPicturaById(arbore->st, id);
		}
		else {
			return arbore->info;
		}
	}
	return p;
}

int determinaNrNoduri(Nod* arbore) {
	if (arbore) {
		int noduriSt = determinaNrNoduri(arbore->st);
		int noduriDr = determinaNrNoduri(arbore->dr);
		return 1 + noduriSt + noduriDr;
	}
	return 0;
}

float calculeazaPretTotal(Nod* arbore) {
	if (arbore) {
		float totalSt = calculeazaPretTotal(arbore->st);
		float totalDr = calculeazaPretTotal(arbore->dr);
		return arbore->info.pret + totalSt + totalDr;
	}
	return 0;
}

float calculeazaPretTotalCentru(Nod* arbore, const char* centru) {
	if (arbore) {
		float totalSt = calculeazaPretTotal(arbore->st);
		float totalDr = calculeazaPretTotal(arbore->dr);
		float sumaCrt = 0;
		if (strcmp(arbore->info.centruExpozitie, centru) == 0) {
			sumaCrt += arbore->info.pret;
		}
		return sumaCrt + totalSt + totalDr;
	}
	return 0;
}

int main() {
	Nod* arbore = citesteArboreDinFisier("picturi.txt");
	afiseazaPreordine(arbore);

	int inaltime = calculInaltime(arbore);
	printf("Inaltimea este:%d\n", inaltime);

	Pictura pictura = getPicturaById(arbore, 1);
	afiseazaPictura(pictura);

	int nrNoduri = determinaNrNoduri(arbore);
	printf("Nr noduri:%d\n", nrNoduri);

	float total = calculeazaPretTotal(arbore);
	printf("Total:%5.2f\n", total);

	float totalFloreasca = calculeazaPretTotalCentru(arbore, "Floreasca");
	printf("Total Floreasca:%5.2f\n", totalFloreasca);
}