#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Laptop {
	int id;
	float pret;
	char* marca;
	char* procesor;
};

typedef struct Laptop Laptop;
typedef struct Nod Nod;

struct Nod {
	Laptop info;
	Nod* st;
	Nod* dr;
};


void afiseazaLaptop(Laptop l) {
	printf("Id:%d\n", l.id);
	printf("Pret:%5.2f\n", l.pret);
	printf("Marca:%s\n", l.marca);
	printf("Procesor:%s\n\n", l.procesor);
}

Laptop citesteLaptopDinFisier(FILE* file) {
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, file);
	char* token;
	Laptop l;
	token = strtok(buffer, delimitator);
	l.id = atoi(token);
	l.pret = atof(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	l.marca = (char*)malloc(strlen(token) + 1);
	strcpy_s(l.marca, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	l.procesor = (char*)malloc(strlen(token) + 1);
	strcpy_s(l.procesor, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return l;
}

void adaugaLaptopInArbore(Nod** arbore, Laptop laptop) {
	if (!(*arbore)) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = laptop;
		nou->st = NULL;
		nou->dr = NULL;
		(*arbore) = nou;
	}
	else {
		if ((*arbore)->info.id > laptop.id) {
			adaugaLaptopInArbore(&((*arbore)->st), laptop);
		}
		else if ((*arbore)->info.id < laptop.id) {
			adaugaLaptopInArbore(&((*arbore)->dr), laptop);
		}
	}
}

Nod* citesteArboreFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(f)) {
		adaugaLaptopInArbore(&arbore, citesteLaptopDinFisier(f));
	}
	fclose(f);
	return arbore;
}

void afiseazaInOrdineSRD(Nod* arbore) {
	if (arbore) {
		afiseazaInOrdineSRD(arbore->st);
		afiseazaLaptop(arbore->info);
		afiseazaInOrdineSRD(arbore->dr);
	}
}

void dezalocaArbore(Nod** arbore) {
	if (*arbore) {
		dezalocaArbore(&(*arbore)->st);
		dezalocaArbore(&(*arbore)->dr);
		free((*arbore)->info.marca);
		free((*arbore)->info.procesor);
		free(*arbore);
		(*arbore) = NULL;
	}
}


Laptop getLaptopById(Nod* arbore, int id) {
	Laptop l;
	l.id = -1;
	if (arbore) {
		if (arbore->info.id < id) {
			return getLaptopById(arbore->dr, id);
		}
		else if (arbore->info.id > id) {
			return getLaptopById(arbore->st, id);
		}
		else {
			return arbore->info;
		}
	}
	return l;
}

int determinaNumarNoduri(Nod* arbore) {
	if (arbore) {
		int noduriSt = determinaNumarNoduri(arbore->st);
		int noduriDr = determinaNumarNoduri(arbore->dr);
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

float calculeazaPretTotalMarca(Nod* arbore, const char* marca) {
	if (arbore) {
		int totalSt = calculeazaPretTotalMarca(arbore->st, marca);
		int totalDr = calculeazaPretTotalMarca(arbore->dr, marca);
		float suma = 0;
		if (strcmp(arbore->info.marca, marca) == 0) {
			suma += arbore->info.pret;
		}
		return suma + totalSt + totalDr;
	}
	return 0;
}
int main() {
	Nod* arbore = citesteArboreFisier("laptops.txt");
	afiseazaInOrdineSRD(arbore);

	float total = calculeazaPretTotal(arbore);
	printf("Total:%5.2f\n", total);


	int nrNoduri = determinaNumarNoduri(arbore);
	printf("Nr noduri:%d\n", nrNoduri);

	float totalMarca = calculeazaPretTotalMarca(arbore, "Asus");
	printf("Total asus:%5.2f\n", totalMarca);

	Laptop l=getLaptopById(arbore, 2);
	afiseazaLaptop(l);

}