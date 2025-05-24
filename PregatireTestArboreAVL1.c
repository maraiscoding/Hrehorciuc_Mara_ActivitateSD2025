//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct Carte {
//	int id;
//	float pret;
//	char* autor;
//	char* editura;
//};
//typedef struct Carte Carte;
//typedef struct Nod Nod;
//
//struct Nod {
//	Carte info;
//	Nod* st;
//	Nod* dr;
//	int gradEchilibru;
//};
//
//
//Carte citesteCarteDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Carte c;
//	token = strtok(buffer, delimitator);
//	c.id = atoi(token);
//	c.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	c.autor = malloc(strlen(token) + 1);
//	strcpy_s(c.autor, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	c.editura = malloc(strlen(token) + 1);
//	strcpy_s(c.editura, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return c;
//}
//
//void afiseazaCarte(Carte c) {
//	printf("Id:%d\n", c.id);
//	printf("Pret:%5.2f\n", c.pret);
//	printf("Autor:%s\n", c.autor);
//	printf("Editura:%s\n\n", c.editura);
//}
//
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
//void rotireDreapta(Nod** arbore) {
//	Nod* aux = (*arbore)->st;
//	(*arbore)->st = aux->dr;
//	aux->dr = (*arbore);
//	(*arbore) = aux;
//	(*arbore)->gradEchilibru++;
//}
//
//void adaugaCarteInArbore(Nod** arbore, Carte carteNoua) {
//	if (!(*arbore)) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = carteNoua;
//		nou->st = NULL;
//		nou->dr = NULL;
//		nou->gradEchilibru = 0;
//		(*arbore) = nou;
//	}
//	else {
//		if ((*arbore)->info.id <= carteNoua.id) {
//			adaugaCarteInArbore(&((*arbore)->dr), carteNoua);
//			(*arbore)->gradEchilibru--;
//		}
//		else {
//			adaugaCarteInArbore(&(*arbore)->st, carteNoua);
//			(*arbore)->gradEchilibru++;
//		}
//		if ((*arbore)->gradEchilibru == 2) {
//			if ((*arbore)->st->gradEchilibru == 1) {
//				rotireDreapta(arbore);
//			}
//			else {
//				rotireStanga(&(*arbore)->st);
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
//int calculeazaInaltime(Nod* radacina) {
//	if (radacina) {
//		int inaltimeSt = calculeazaInaltime(radacina->st);
//		int inaltimeDr = calculeazaInaltime(radacina->dr);
//		if (inaltimeSt > inaltimeDr) {
//			return 1 + inaltimeSt;
//		}
//		else {
//			return 1 + inaltimeDr;
//		}
//	}
//	else {
//		return 0;
//	}
//}
//
//Nod* citesteArboreDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* arbore = NULL;
//	while (!feof(f)) {
//		adaugaCarteInArbore(&arbore, citesteCarteDinFisier(f));
//	}
//	fclose(f);
//	return arbore;
//}
//
//void afisarePreordineRSD(Nod* arbore) {
//	if (arbore) {
//		afiseazaCarte(arbore->info);
//		afisarePreordineRSD(arbore->st);
//		afisarePreordineRSD(arbore->dr);
//	}
//}
//
//
//int determinaNumarNoduri(Nod* arbore) {
//	if (arbore) {
//		int noduriSt = determinaNumarNoduri(arbore->st);
//		int noduriDr = determinaNumarNoduri(arbore->dr);
//		return 1 + noduriDr + noduriSt;
//}
//	return 0;
//}
//
//float calculeazaPretTotal(Nod* arbore) {
//	if (arbore) {
//		float totalSt = calculeazaPretTotal(arbore->st);
//		float totalDr = calculeazaPretTotal(arbore->dr);
//		return arbore->info.pret + totalSt + totalDr;
//	}
//	return 0;
//}
//
//float calculeazaPretTotalEditura(Nod* arbore, const char* editura) {
//	if (arbore) {
//		float totalSt = calculeazaPretTotalEditura(arbore->st, editura);
//		float totalDr = calculeazaPretTotalEditura(arbore->dr, editura);
//		float sumaCrt = 0;
//		if (strcmp(arbore->info.editura, editura) == 0) {
//			sumaCrt += arbore->info.pret;
//		}
//		return sumaCrt + totalSt + totalDr;
//	}
//	return 0;
//}
//
//
//Carte getCarteById(Nod* arbore, int id) {
//	Carte c;
//	c.id = -1;
//	if (arbore) {
//		if (arbore->info.id < id) {
//			return getCarteById(arbore->dr, id);
//		}
//		else if (arbore->info.id > id) {
//			return getCarteById(arbore->st, id);
//		}
//		else {
//			return arbore->info;
//		}
//	}
//	return c;
//}
//
//
//int main() {
//	Nod* arbore = citesteArboreDinFisier("carti.txt");
//	afisarePreordineRSD(arbore);
//
//	int inaltime = calculeazaInaltime(arbore);
//	printf("Inaltimea e:%d\n", inaltime);
//
//	Carte c = getCarteById(arbore, 1);
//	afiseazaCarte(c);
//
//	float total = calculeazaPretTotal(arbore);
//	printf("pret total: % 5.2f\n", total);
//
//	float totalArt = calculeazaPretTotalEditura(arbore, "Art");
//	printf("pret total art:%5.2f\n", totalArt);
//
//	int nrNoduri = determinaNumarNoduri(arbore);
//	printf("Nr noduri:%d\n", nrNoduri);
//}