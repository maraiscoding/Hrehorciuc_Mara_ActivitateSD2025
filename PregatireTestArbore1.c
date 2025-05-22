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
	Nod* st;
	Nod* dr;
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

void adaugaCarteInArbore(Nod** arbore, Carte carteNoua) {
	if (!(*arbore)) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = carteNoua;
		nou->st = NULL;
		nou->dr = NULL;
		(*arbore) = nou;
	}
	else {
		if ((*arbore)->info.id > carteNoua.id) {
			adaugaCarteInArbore(&((*arbore)->st), carteNoua);
		}
		else if ((*arbore)->info.id < carteNoua.id) {
			adaugaCarteInArbore(&((*arbore)->dr), carteNoua);
		}
	}
}

Nod* citesteArboreDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(f)) {
		adaugaCarteInArbore(&arbore, citesteCarteDinFisier(f));
	}
	fclose(f);
	return arbore;
}

void afiseazaInOrdineSRD(Nod* arbore) {
	if (arbore) {
		afiseazaInOrdineSRD(arbore->st);
		afiseazaCarte(arbore->info);
		afiseazaInOrdineSRD(arbore->dr);
	}
}

void afiseazaPreordineRSD(Nod* arbore) {
	if (arbore) {
		afiseazaCarte(arbore->info);
		afiseazaPreordineRSD(arbore->st);
		afiseazaPreordineRSD(arbore->dr);
	}
}

void afiseazaPostordineSDR(Nod* arbore) {
	if (arbore) {
		afiseazaPostordineSDR(arbore->st);
		afiseazaPostordineSDR(arbore->dr);
		afiseazaCarte(arbore->info);
	}
}

void dezalocaArbore(Nod** arbore) {
	if (*arbore) {
		free(&(*arbore)->st);
		free(&(*arbore)->dr);
		free((*arbore)->info.editura);
		free((*arbore)->info.autor);
		free(*arbore);
		*arbore = NULL;
	}
}


Carte getCarteById(Nod* arbore, int id) {
	Carte c;
	c.id = -1;
	if (arbore) {
		if (arbore->info.id < id) {
			return getCarteById(arbore->dr, id);
		}
		else if (arbore->info.id > id) {
			return getCarteById(arbore->st, id);
		}
		else {
			return arbore->info;
		}
	}
	return c;
}

int calculeazaNumarNoduri(Nod* arbore) {
	if (arbore) {
		int noduriSt = calculeazaNumarNoduri(arbore->st);
		int noduriDr = calculeazaNumarNoduri(arbore->dr);
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

float calculeazaPretTotalEditura(Nod* arbore, const char* editura) {
	if (arbore) {
		float totalSt = calculeazaPretTotalEditura(arbore->st, editura);
		float totalDr = calculeazaPretTotalEditura(arbore->dr, editura);
		float sumaCrt = 0;
		if (strcmp(arbore->info.editura, editura) == 0) {
			sumaCrt += arbore->info.pret;
		}
		return sumaCrt + totalSt + totalDr;
		}
	return 0;
}

int main() {
	Nod* arbore = citesteArboreDinFisier("carti.txt");
	afiseazaInOrdineSRD(arbore);


	Carte c = getCarteById(arbore, 1);
	afiseazaCarte(c);

	int nrNoduri = calculeazaNumarNoduri(arbore);
	printf("nr noduri:%d\n", nrNoduri);

	float total = calculeazaPretTotal(arbore);
	printf("total:%5.2f\n", total);

	float totalEditura = calculeazaPretTotalEditura(arbore, "Art");
	printf("pret total Art:%5.2f\n", totalEditura);

}