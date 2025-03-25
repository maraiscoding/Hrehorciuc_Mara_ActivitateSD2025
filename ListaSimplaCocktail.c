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
};

void afisareCocktail(Cocktail c) {
	printf("Id:%d\n", c.id);
	printf("Numar ingrediente:%d\n", c.nrIngrediente);
	printf("Pret:%5.2f\n", c.pret);
	printf("Denumire:%s\n", c.denumire);
	printf("Origine:%s\n\n", c.origine);
}

void afisareListaCocktails(Nod* cap) {
	while (cap) {
		afisareCocktail(cap->info);
		cap = cap->next;
	}
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

void adaugaLaFinal(Nod** cap, Cocktail cocktailNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = cocktailNou;
	nou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		Nod* p = (*cap);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}

void adaugaLaInceput(Nod** cap, Cocktail cocktailNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = cocktailNou;
	nou->next = (*cap);
	(*cap) = nou;
}

Nod* citesteListaCocktailsFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaLaFinal(&lista, citesteCocktailDinFisier(f));
	}
	fclose(f);
	return lista;
}

float calculeazaPretMediu(Nod* lista) {
	if (!lista) {
		return 0;
	}
	float suma = 0;
	int count = 0;
	while (lista) {
		suma += lista->info.pret;
		count++;
		lista = lista->next;
	}
	return suma / count;
}

float calculeazaPretTotalOrigine(Nod* lista, const char* origine) {
	float suma = 0;
	while (lista) {
		if (strcmp(lista->info.origine, origine) == 0) {
			suma += lista->info.pret;
		}
		lista = lista->next;
	}
	return suma;
}

void modificaDenumire(Nod* lista, const char* denumire, const char* denumireNoua) {
	while (lista) {
		if (strcmp(lista->info.denumire, denumire) == 0) {
			free(lista->info.denumire);
			lista->info.denumire = (char*)malloc(sizeof(char)*(strlen(denumireNoua) + 1));
			strcpy_s(lista->info.denumire, strlen(lista->info.denumire) + 1, denumireNoua);
		}
		lista = lista->next;
	}
}

char* getCelMaiScumpCocktail(Nod* lista) {
	float pretulMaxim = 0;
	char* numeScump = 0;
	while (lista) {
		if (lista->info.pret > pretulMaxim) {
			pretulMaxim = lista->info.pret;
			numeScump = lista->info.denumire;
		}
		lista = lista->next;
	}
	if (pretulMaxim > 0) {
		char* nou = (char*)malloc(strlen(numeScump) + 1);
		strcpy_s(nou, strlen(numeScump) + 1, numeScump);
		return nou;
	}
	else { return NULL;  }
}
int main() {
		Nod* cap = NULL;
		cap = citesteListaCocktailsFisier("cocktails.txt");
		afisareListaCocktails(cap);

		printf("Pretul mediu este:%5.2f\n", calculeazaPretMediu(cap));
		printf("Pretul cocktail-urilor din Spania este:%5.2f\n", calculeazaPretTotalOrigine(cap, "Spania"));
	
		modificaDenumire(cap, "Cuba Libre", "CubaLibre");
		printf("Lista dupa modificare:");
		afisareListaCocktails(cap);

		printf("%s\n", getCelMaiScumpCocktail(cap));
}