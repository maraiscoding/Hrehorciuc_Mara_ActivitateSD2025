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

void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nou;
	} else {
		Nod* p = (*cap);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}

//Nod** pt ca adaugam la inceput si modificam adresa primului
void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = cap;
	(*cap) = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

Nod* citireListaMasiniDinFisier1(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareListaMasini(Nod** cap) {
	while ((*cap) != NULL) {
		Nod* aux = (*cap);
		*cap = (*cap)->next;
		free(aux->info.numeSofer);
		free(aux->info.model);
		free(aux);
	}
}

float calculeazaPretMediu(Nod* lista) {
	if (!lista) {
		return 0;
	}
	int count = 0;
	float suma = 0;
	while (lista) {
		suma += lista->info.pret;
		count++;
		lista = lista->next;
	}
	return suma / count;
}

void stergeMasiniDinSeria(Nod** lista, char serieCautata) {
	Nod* p = *lista;
	while (p != NULL && p->info.serie == serieCautata) {
		Nod* sters = p;
		p = p->next;

		free(sters->info.model);
		free(sters->info.numeSofer);
		free(sters);
	}

	*lista = p;
	if (p != NULL) {
		Nod* ant = p;
		Nod* curent = p->next;
		while (curent != NULL) {
			if (curent->info.serie == serieCautata) {
				Nod* sters = curent;
				ant->next = curent->next;
				curent = curent->next;

				free(sters->info.model);
				free(sters->info.numeSofer);
				free(sters);
			}
			else {
				ant = curent;
				curent = curent->next;
			}
		}

	}
}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	float suma = 0;
	while (lista) {
		if (strcmp(numeSofer, lista->info.numeSofer) == 0) {
			suma += lista->info.pret;
		}
		lista = lista->next;
	}
	return suma;
}

char* getCeaMaiScumpaMasina(Nod* lista) {
	float pretulMaxim = 0;
	char* modelScump = NULL;
	while (lista) {
		if (lista->info.pret > pretulMaxim) {
			pretulMaxim = lista->info.pret;
			modelScump = lista->info.model;
		}
		lista = lista->next;
	}
	if (pretulMaxim > 0) {
		char* nou = malloc(strlen(modelScump));
		strcpy_s(nou, strlen(modelScump) + 1, modelScump);
		return nou;
	}
	else {
		return NULL;
	}
}

int main() {
	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("masini2.txt");
	afisareListaMasini(cap);

	float pretMediu = calculeazaPretMediu(cap);
	printf("Pretul mediu este: %5.2f\n", pretMediu);

	float pretSofer = calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu");
	printf("Pretul masinilor lui Ionescu este: %5.2f", pretSofer);

	printf("\n%s", getCeaMaiScumpaMasina(cap));

	char serieCautata = 'A';
	stergeMasiniDinSeria(&cap, serieCautata);
	printf("Seria dupa stergere:\n");
	afisareListaMasini(cap);

	dezalocareListaMasini(&cap);

	
	
	return 0;
}