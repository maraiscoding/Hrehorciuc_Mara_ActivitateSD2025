//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//struct Cocktail {
//	int id;
//	int nrIngrediente;
//	float pret;
//	char* denumire;
//	char* origine;
//};
//
//typedef struct Cocktail Cocktail;
//typedef struct Nod Nod;
//
//struct Nod {
//	Cocktail info;
//	Nod* st;
//	Nod* dr;
//	int gradEchilibru;
//};
//
//void afisareCocktail(Cocktail c) {
//	printf("Id:%d\n", c.id);
//	printf("Numar ingrediente:%d\n", c.nrIngrediente);
//	printf("Pret:%5.2f\n", c.pret);
//	printf("Denumire:%s\n", c.denumire);
//	printf("Origine:%s\n\n", c.origine);
//}
//
//Cocktail citesteCocktailDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Cocktail c;
//	token = strtok(buffer, delimitator);
//	c.id = atoi(token);
//	c.nrIngrediente = atoi(strtok(NULL, delimitator));
//	c.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	c.denumire = malloc(strlen(token) + 1);
//	strcpy_s(c.denumire, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	c.origine = malloc(strlen(token) + 1);
//	strcpy_s(c.origine, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return c;
//}
//
//void rotireDreapta(Nod** arbore) {
//	Nod* aux = (*arbore)->st;
//	(*arbore)->st = aux->dr;
//	aux->dr = (*arbore);
//	(*arbore) = aux;
//	(*arbore)->gradEchilibru++;
//}
//
//void rotireStanga(Nod** arbore) {
//	Nod* aux = (*arbore)->dr;
//	(*arbore)->dr = aux->st;
//	aux->st = (*arbore);
//	(*arbore) = aux;
//	(*arbore)->gradEchilibru--;
//}
//
//
//void adaugaCocktailInArbore(Nod** arbore, Cocktail cocktail) {
//	if (!(*arbore)) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = cocktail;
//		nou->st = NULL;
//		nou->dr = NULL;
//		nou->gradEchilibru = 0;
//		(*arbore) = nou;
//	}
//	else {
//		if ((*arbore)->info.id <= cocktail.id) {
//			adaugaCocktailInArbore(&((*arbore)->dr), cocktail);
//			(*arbore)->gradEchilibru--;
//		}
//		else {
//			adaugaCocktailInArbore(&((*arbore)->st), cocktail);
//			(*arbore)->gradEchilibru++;
//		}
//		if ((*arbore)->gradEchilibru == 2) {
//			if ((*arbore)->st->gradEchilibru == 1) {
//				rotireDreapta(arbore);
//			}
//			else {
//				rotireStanga(&((*arbore)->st));
//				rotireDreapta(arbore);
//			}
//		}
//		else if ((*arbore)->gradEchilibru == -2) {
//			if ((*arbore)->dr->gradEchilibru != -1) {
//				rotireDreapta(&((*arbore)->dr));
//			}
//			rotireStanga(arbore);
//		}
//	}
//}
//
//void dezalocaArbore(Nod** arbore) {
//	if (*arbore) {
//		dezalocaArbore(&((*arbore)->st));
//		dezalocaArbore(&((*arbore)->dr));
//		free((*arbore)->info.denumire);
//		free((*arbore)->info.origine);
//		free(*arbore);
//		(*arbore) = NULL;
//	}
//}
//
//int calculInaltime(Nod* arbore) {
//	if (arbore) {
//		int inaltimeSt = calculInaltime(arbore->st);
//		int inaltimeDr = calculInaltime(arbore->dr);
//		if (inaltimeSt > inaltimeDr) {
//			return 1 + inaltimeSt;
//		}
//		else {
//			return 1 + inaltimeDr;
//		}
//	}
//	return 0;
//}
//
//void afisareInOrdine(Nod* arbore) {
//	if (arbore) {
//		afisareInOrdine(arbore->st);
//		afisareCocktail(arbore->info);
//		afisareInOrdine(arbore->dr);
//	}
//}
//
//Nod* citesteArboreDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* arbore = NULL;
//	while (!feof(f)) {
//		adaugaCocktailInArbore(&arbore, citesteCocktailDinFisier(f));
//	}
//	fclose(f);
//	return arbore;
//}
//
//Cocktail getCocktailByID(Nod* arbore, int id) {
//	Cocktail c;
//	c.id = -1;
//	if (arbore) {
//		if (arbore->info.id < id) {
//			return getCocktailByID(arbore->dr, id);
//		}
//		else if (arbore->info.id > id) {
//			return getCocktailByID(arbore->st, id);
//		}
//		else {
//			return arbore->info;
//		}
//	}
//	return c;
//}
//
//
//int determinaNrNoduri(Nod* arbore) {
//	if (arbore) {
//		int noduriSt = determinaNrNoduri(arbore->st);
//		int noduriDr = determinaNrNoduri(arbore->dr);
//		return 1 + noduriSt + noduriDr;
//	}
//	return 0;
//}
//
//float calculeazaPretTotal(Nod* arbore) {
//	if (arbore) {
//		int totalSt = calculeazaPretTotal(arbore->st);
//		int totalDr = calculeazaPretTotal(arbore->dr);
//		return arbore->info.pret + totalSt + totalDr;
//	}
//	return 0;
//}
//
//float calculeazaPretOrigine(Nod* arbore, const char* origine) {
//	if (arbore) {
//		int totalSt = calculeazaPretOrigine(arbore->st, origine);
//		int totalDr = calculeazaPretOrigine(arbore->dr, origine);
//		int suma = 0;
//		if (strcmp(arbore->info.origine, origine) == 0) {
//			suma += arbore->info.pret;
//		}
//		return suma + totalSt + totalDr;
//	}
//	return 0;
//}
//
//
//int main() {
//	Nod* arbore = citesteArboreDinFisier("cocktails.txt");
//	afisareInOrdine(arbore);
//
//	int inaltime = calculInaltime(arbore);
//	printf("inaltimea e :%d\n", inaltime);
//
//	int noduri = determinaNrNoduri(arbore);
//	printf("Nr noduri:%d\n", noduri);
//
//	Cocktail c = getCocktailByID(arbore, 1);
//	afisareCocktail(c);
//
//	float suma = calculeazaPretTotal(arbore);
//	printf("total:%5.2f\n", suma);
//
//	float sumao = calculeazaPretOrigine(arbore, "Spania");
//	printf("suma spania:%5.2f\n", sumao);
//}